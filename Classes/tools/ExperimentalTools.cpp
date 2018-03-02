#include "ExperimentalTools.h"
#include "ui/UIScale9Sprite.h"
USING_NS_CC;
std::string ExperimentalTools::wstrToUTF8(const std::wstring & wstr)
{
	std::string dest;

	dest.clear();
	for (size_t i = 0; i < wstr.size(); i++)
	{

		wchar_t w = wstr[i];
		if (w <= 0x7f)
			dest.push_back((char)w);
		else if (w <= 0x7ff)
		{
			dest.push_back(0xc0 | ((w >> 6) & 0x1f));
			dest.push_back(0x80 | (w & 0x3f));
		}
		else if (w <= 0xffff)
		{

			dest.push_back(0xe0 | ((w >> 12) & 0x0f));
			dest.push_back(0x80 | ((w >> 6) & 0x3f));
			dest.push_back(0x80 | (w & 0x3f));
		}
		else if (sizeof(wchar_t) > 2 && w <= 0x10ffff)
		{
			dest.push_back(0xf0 | ((w >> 18) & 0x07));
			// wchar_t 4-bytes situation          
			dest.push_back(0x80 | ((w >> 12) & 0x3f));
			dest.push_back(0x80 | ((w >> 6) & 0x3f));
			dest.push_back(0x80 | (w & 0x3f));
		}
		else
			dest.push_back('?');
	}
	return dest;
}

void ExperimentalTools::parseIntDataByMark(std::string str, std::vector<int>& data, const std::string & separator)
{
	CCASSERT(separator.size() == 1, "just a char");
	data.clear();
	while (!str.empty())
	{
		auto index = str.find(separator);

		if (index == std::string::npos)
		{
			data.push_back(atoi(str.c_str()));
			break;
		}
		else
		{
			data.push_back(atoi(str.substr(0, index).c_str()));
		}

		str = str.substr(index + 1);
	}
}

void ExperimentalTools::createOutline(cocos2d::Node * node, const cocos2d::Color4B & color)
{
	auto outColor = LayerColor::create(color);
	outColor->setBlendFunc(BlendFunc{ GL_DST_ALPHA, GL_ZERO });

	auto lineWidth = 1.05f;
	auto contentSize = node->getContentSize();
	auto oldPos = node->getPosition();
	auto anchorPoint = Vec2::ZERO;
	auto oldScale = node->getScale();
	if (!node->isIgnoreAnchorPointForPosition())
	{
		anchorPoint = node->getAnchorPoint();
	}

	node->setScale(lineWidth);
	node->setPosition(lineWidth * contentSize.width * anchorPoint.x, lineWidth * contentSize.height * anchorPoint.y);

	auto render = RenderTexture::create(contentSize.width * lineWidth, contentSize.height* lineWidth);
	render->clear(0.f, 0.f, 0.f, 0.f);
	render->begin();
	node->visit();
	outColor->visit();
	render->end();

	node->setScale(oldScale);
	node->setPosition(oldPos);

	cocos2d::Director::getInstance()->getRenderer()->render();
	auto texture = render->getSprite()->getTexture();
	auto outline = Sprite::createWithTexture(texture);
	outline->setPosition(contentSize.width * oldScale * 0.5f, contentSize.height * oldScale * 0.5f);
	outline->setFlippedY(true);

	node->addChild(outline, -1, "outline");
}

void ExperimentalTools::createInline(cocos2d::Node * node, const cocos2d::Color4B & color)
{
}

void ExperimentalTools::btnScaleEffect(cocos2d::ui::Button * btn, cocos2d::ui::Widget::TouchEventType type, float scale)
{
	if (type == ui::Widget::TouchEventType::BEGAN)
	{
		btn->setScale(btn->getScale() * scale);
	}
	else if(type == ui::Widget::TouchEventType::ENDED || type == ui::Widget::TouchEventType::CANCELED)
	{
		btn->setScale(btn->getScale() / scale);
	}
}

