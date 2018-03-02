#include "LearnScene_2.h"
#include <chrono>
#include "ui/UIPageView.h"
#include "cocostudio\CocoStudio.h"
#include "ui/UIButton.h"
#include <fstream>
#include <spine/spine-cocos2dx.h>
#include "spine/spine.h"
#include "RibbonTrail.h"
#include "tools/ExperimentalTools.h"

//gif
//#include "Gif/GIFMovie.h"
//#include "Gif/CacheGif.h"
//#include "Gif/CacheGifData.h"
//#include "Gif/InstantGif.h"
//#include "Gif/InstantGifData.h"

const int ROW = 15;
const int COLUMN = 10;

USING_NS_CC;
bool LearnScene_2::init()
{
	if(!Scene::init())
		return false;

	//AboutChrono();
	//AboutTime_t();
	//AboutAStart();
	//AboutWStrToUTF8();
	//AboutShader();
	//AboutRenderTexture();
	//AboutTransitionScene();
	//AboutIO();
	//AboutSpine();
	//AboutPageView();
	//AboutThread();
	//AboutMotionStreak();
	//AboutOutline();
	//AboutShaderOutline();
	//AboutGif();
	AboutWriteXML();

	return true;
}

void LearnScene_2::AboutChrono()
{
	//duration
	using seconds_type = std::chrono::duration<int>;
	std::chrono::duration<int> sec(60);
	std::chrono::duration<int, std::milli> millSec(1000 * 60);
	std::chrono::duration<int, std::ratio<60 * 60>> hour(1);
	log("%dms in hourt", std::chrono::duration_cast<std::chrono::duration<int, std::milli>>(hour).count());

	//time_point
	std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds> tp_seconds(std::chrono::seconds(1));
	log("since epoch %d", tp_seconds.time_since_epoch().count());

	//steady count
	std::chrono::time_point<std::chrono::steady_clock> cur = std::chrono::steady_clock::now();
	for (auto i = 0; i < 1000; i++);
	std::chrono::time_point<std::chrono::steady_clock> now = std::chrono::steady_clock::now();
	std::chrono::duration<double> delta = std::chrono::duration_cast<std::chrono::duration<double>>(now - cur);
	log("count %lf", delta.count());

	std::chrono::time_point<std::chrono::high_resolution_clock> t1 = std::chrono::high_resolution_clock::now();
	for (auto i = 0; i < 10000; i++);
	std::chrono::time_point<std::chrono::high_resolution_clock> t2 = std::chrono::high_resolution_clock::now();
	std::chrono::nanoseconds span = t2 - t1;
	//explicit cast  duration cast
	std::chrono::duration<double> spp = std::chrono::duration_cast<std::chrono::duration<double>>(span);
	//implicit cast duration cast
	std::chrono::duration<double> sppaa(span);
	log("count %ld", span.count());
	log("count %lf", spp.count());

	std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds> tt1(std::chrono::seconds(1));
	std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> tt2(tt1);
	std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> tt3 = std::chrono::time_point_cast<std::chrono::milliseconds>(tt1);
	//std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<int>> delta = std::chrono::time_point_cast<std::chrono::steady_clock, std::chrono::duration<int>>(now - sec);
}

void LearnScene_2::AboutTime_t()
{
	//read : http://blog.csdn.net/luoweifu/article/details/20288549

	//year month day  hour minute seconds 
	time_t timep;
	//seconds uSeconds
	timeval tv;
	time(&timep);
	
	gettimeofday(&tv, nullptr);

	log("%s", asctime(gmtime(&timep)));
	log("%s", ctime(&timep));
}

void LearnScene_2::AboutAStart()
{
	openList.clear();
	closeList.clear();

	auto origin = Vec2(100, 100);
	//obstacle.push_back(Vec2(9, 9));
	//obstacle.push_back(Vec2(9, 8));
	//obstacle.push_back(Vec2(9, 7));
	//obstacle.push_back(Vec2(9, 6));
	//obstacle.push_back(Vec2(9, 5));
	//obstacle.push_back(Vec2(9, 4));
	//obstacle.push_back(Vec2(9, 3));
	//obstacle.push_back(Vec2(9, 2));
	//obstacle.push_back(Vec2(9, 1));
	//obstacle.push_back(Vec2(9, 0));
	//obstacle.push_back(Vec2(5, 7));
	//obstacle.push_back(Vec2(5, 8));
	//obstacle.push_back(Vec2(5, 9));
	//obstacle.push_back(Vec2(6, 3));
	//obstacle.push_back(Vec2(2, 8));
	//obstacle.push_back(Vec2(7, 5));

	begin = Vec2(3, 2);
	destination = Vec2(10, 9);

	for (auto i = 0; i < COLUMN; i++)
	{
		for (auto j = 0; j < ROW; j++)
		{
			auto layer = LayerColor::create(Color4B::WHITE, 30, 30);
			layer->setPosition(origin + Vec2(15 + j * (30 + 5), 15 + i * (30 + 5)));
			layer->setTag(j * 100 + i);
			this->addChild(layer);
		}
	}

	this->getChildByTag(begin.x * 100 + begin.y)->setColor(Color3B::GREEN);
	this->getChildByTag(destination.x * 100 + destination.y)->setColor(Color3B::BLUE);
	std::for_each(obstacle.begin(), obstacle.end(), [this](Vec2 point)
	{
		this->getChildByTag(point.x * 100 + point.y)->setColor(Color3B::RED);
	});

	//start
	auto point = new PointInfo();
	point->coordinate = begin;
	point->g = 0;
	point->h = 0;
	point->parent = nullptr;
	putPointIntoCloseList(point);
}

void LearnScene_2::AboutWStrToUTF8()
{
	std::string dest;
	std::wstring src = L"真的勇士要敢于挑战英雄的难度！";

	dest.clear();
	for (size_t i = 0; i < src.size(); i++)
	{

		wchar_t w = src[i];
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

	Label* label = Label::createWithSystemFont(dest, "Arial", 50);
	this->addChild(label);
	label->setPosition(Vec2(500, 100));
	label->setColor(Color3B::RED);
}

void LearnScene_2::AboutShader()
{
	auto sp = Sprite::create("bg_yue.png");
	sp->setPosition(Vec2(300, 200));
	this->addChild(sp);

	auto glProgram = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_GRAYSCALE);
	glProgram->use();
	glProgram->setUniformsForBuiltins();

	sp->setGLProgram(glProgram);

	sp->runAction(Sequence::create(
		DelayTime::create(2.0f),
		CallFuncN::create([](cocos2d::Node* node) {
			auto glProgram = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP);
			node->setGLProgram(glProgram);
			glProgram->use();
			glProgram->setUniformsForBuiltins();
		}),
		nullptr
	));
}

void LearnScene_2::AboutRenderTexture()
{
	auto visible = Director::getInstance()->getVisibleSize();
	auto layer = LayerColor::create(Color4B::GRAY, visible.width, visible.height);
	layer->setCameraMask(2);
	layer->retain();
	this->addChild(layer, -2);

	auto csb = CSLoader::createNode("naruto/Enemy_1.csb");
	csb->setAnchorPoint(Vec2(0.5f, 0.5f));
	csb->setCameraMask(2);
	csb->setContentSize(Size(500, 500));
	csb->setPosition(100, visible.height / 2);
	//auto timeline = CSLoader::createTimeline("naruto/Enemy_1.csb");
	//csb->runAction(timeline);
	//timeline->gotoFrameAndPlay(0, true);
	this->addChild(csb);

	//auto render = RenderTexture::create(visible.width, visible.height, Texture2D::PixelFormat::RGBA8888);
	//render->setVirtualViewport(Vec2(-200, -400), Rect(0, 0, visible.width, visible.height), Rect(0, 0, visible.width, visible.height));
	//render->beginWithClear(0.f, 0.f, 0.f, 0.f);
	//layer->visit();
	//csb->visit();
	//render->end();

	//auto sp = Sprite::createWithTexture(render->getSprite()->getTexture());
	//sp->setFlippedY(true);
	//sp->setPosition(100, 400);
	//this->addChild(sp);

	/*auto layer = LayerColor::create(Color4B::RED, 50, 50);
	layer->setPosition(50, visible.height /2);
	this->addChild(layer);*/

	auto act = RepeatForever::create(
		Sequence::create(
			MoveBy::create(1.0f, Vec2(400, 0)),
			MoveBy::create(1.0f, Vec2(-400, 0)),
			MoveBy::create(1.0f, Vec2(0, 400)),
			MoveBy::create(1.0f, Vec2(0, -400)),
			nullptr
		)
	);

	auto camera = Camera::create();
	camera->setCameraFlag(CameraFlag::USER1);
	csb->addChild(camera);

	//幻影
	csb->runAction(act);
	//camera->runAction(act->clone());

	auto image = utils::captureNode(csb);
	auto texture = TextureCache::getInstance()->addImage(image, "csb");
	
	schedule(
		[csb, visible, this, texture](float dt)
	{

		//auto b = image->saveToFile(StringUtils::format("pic_%d.png", index++));

		//render->beginWithClear(0, 0, 0, 0);
		//csb->getChildren().at(0)->visit();
		//csb->getChildren().at(1)->visit();
		//render->end();
		auto sp = Sprite::createWithTexture(texture);
		//sp->setAnchorPoint(Vec2::ZERO);
		sp->setCameraMask(2);
		sp->setPosition(csb->getPosition());
		this->addChild(sp, -1);
		//sp->setOpacity(100);
					//sp->setAnchorPoint(Vec2::ZERO);
					//log("posX :%.2f posY%.2f", layer->getPosition().x, layer->getPosition().y);
		//sp->setPosition(visible/2);
		//sp->setFlippedY(true);
		//this->addChild(sp, -1);

		sp->runAction(
			Sequence::create(
				FadeOut::create(0.6f),
				RemoveSelf::create(),
				nullptr
				)
			);

	}, 0.2f, "shadow");
	


	/*正片叠底
	auto sp = Sprite::create("externRec/blend/frost.png");
	sp->setPosition(visible / 2);
	sp->retain();

	schedule(
		[csb, sp, visible, this](float dt)
	{
		auto render = RenderTexture::create(visible.width, visible.height, cocos2d::Texture2D::PixelFormat::RGBA8888);
		render->beginWithClear(0, 0, 0, 0);
		csb->visit();
		render->end();

		sp->setBlendFunc(BlendFunc{ GL_DST_ALPHA, GL_ZERO });
		render->begin();
		sp->visit();
		render->end();

		this->removeChildByName("clip");
		auto cover = Sprite::createWithTexture(render->getSprite()->getTexture());
		cover->setFlippedY(true);
		cover->setPosition(visible / 2);
		cover->setBlendFunc(BlendFunc{ GL_DST_COLOR, GL_ONE });
		this->addChild(cover);
		cover->setName("clip");
	}, 0.1f,
		"test");
		*/
		
}

void LearnScene_2::AboutTransitionScene()
{
	this->runAction(
		Sequence::create(
			DelayTime::create(1.0f),
			CallFunc::create(
				[]() {Director::getInstance()->replaceScene(P_TransitionScene::create(1.f, Scene::create())); }
			)
			, nullptr
		)
	);
}

void LearnScene_2::AboutIO()
{
	///C
	/*
	std::chrono::time_point<std::chrono::steady_clock> cur = std::chrono::steady_clock::now();
	FILE* read = fopen("F:/Proj-Learn/TestAndLearn/Resources/TowerDefense.apk", "rb+");
	if (read)
	{
		FILE* write = fopen("F:/Proj-Learn/TestAndLearn/Resources/abc", "wb+");
		while (!feof(read))
		{
			unsigned char buffer[1024];
			fread(buffer, 1024, 1, read);
			fwrite(buffer, 1024, 1, write);
		}
		fclose(read);
		fclose(write);

		std::chrono::time_point<std::chrono::steady_clock> now = std::chrono::steady_clock::now();
		std::chrono::duration<int, std::milli> delta = std::chrono::duration_cast<std::chrono::duration<int, std::milli>>(now - cur);
		log("count %ld", delta.count());
	}
	*/

	///c++
	/*
	std::ifstream read;
	std::ofstream write;
	read.open("F:/Proj-Learn/TestAndLearn/Resources/TowerDefense.apk", std::ifstream::in | std::ifstream::binary);
	if (read)
	{
		std::chrono::time_point<std::chrono::steady_clock> cur = std::chrono::steady_clock::now();
		write.open("F:/Proj-Learn/TestAndLearn/Resources/abc", std::ifstream::out | std::ifstream::binary);
		write << read.rdbuf();
		read.close();
		write.close();
		std::chrono::time_point<std::chrono::steady_clock> now = std::chrono::steady_clock::now();
		std::chrono::duration<int, std::milli> delta = std::chrono::duration_cast<std::chrono::duration<int, std::milli>>(now - cur);
		log("count %ld", delta.count());
	}
	*/
}

void LearnScene_2::AboutSpine()
{
	auto skeletonNode = spine::SkeletonAnimation::createWithJsonFile("spine/baishu.json", "spine/baishu.atlas");
	skeletonNode->setPosition(300, 300);
	this->addChild(skeletonNode);

	skeletonNode->setAnimation(0, "hurt", false);
	skeletonNode->addAnimation(0, "hurt2", false);
	skeletonNode->addAnimation(0, "jump_down", false);
	skeletonNode->addAnimation(0, "jump_first", false);
	skeletonNode->addAnimation(0, "jump_start", false);
	skeletonNode->addAnimation(0, "stand", false);
	skeletonNode->addAnimation(0, "walk", false);
	skeletonNode->addAnimation(0, "dead", false);
}

void LearnScene_2::AboutPageView()
{
	using namespace ui;
	PageView* pageView = PageView::create();
	pageView->setAnchorPoint(Vec2(0.5f, 0.5f));
	pageView->setDirection(PageView::Direction::HORIZONTAL);
	pageView->setContentSize(Size(300, 300));
	pageView->setPosition(Vec2(360, 400));
	pageView->removeAllItems();
	//pageView->setAutoScrollStopEpsilon(0.05f);
	//pageView->setIndicatorEnabled(true);

	for (auto i = 0; i < 15; i++)
	{
		ui::Layout* layout = ui::Layout::create();
		layout->setAnchorPoint(Vec2(0.5f, 0.5f));
		layout->setContentSize(Size(300, 300));

		auto sp = Sprite::create("HelloWorld.png");
		sp->setPosition(150, 150);
		layout->addChild(sp);

		pageView->pushBackCustomItem(layout);
	}

	auto btn = ui::Button::create("tree2.png");
	btn->setPosition(Vec2(300, 1000));
	this->addChild(btn);
	btn->addClickEventListener([pageView](cocos2d::Ref* ) 
	{
		auto index = pageView->getCurPageIndex();
		index++;
		if(index > 14)
		{ 
			index = 0;
			pageView->setCurPageIndex(0);
		}
		else
		{
			pageView->scrollToPage(index);
		}
		
	});

	this->addChild(pageView);
}

void LearnScene_2::AboutThread()
{
	t = new ticket();
}

void LearnScene_2::AboutMissile()
{




}

void LearnScene_2::AboutMotionStreak()
{
	auto motion = MotionStreak::create(0.5f, 10, 82, Color3B::WHITE, "trail.png");
	motion->setGLProgramState(GLProgramState::getOrCreateWithShaders("shader/ccShader_PositionTexture_uColor.vert", "shader/ccShader_PositionTexture_uColor.frag", ""));
	
	motion->setPosition(200, 700);
	this->addChild(motion);
	//motion->runAction(EaseIn::create(MoveBy::create(10.f, Vec2(0, 1000)), 0.5f));
	_scheduler->schedule([motion, this](float dt)
		{
			motion->setPosition(Vec2(motion->getPositionX(), motion->getPositionY() + dt * 1000));
			this->getDefaultCamera()->setPositionY(this->getDefaultCamera()->getPositionY() + dt * 1000);
		}, this, 0, false, "1"
	);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [motion](cocos2d::Touch* touch, cocos2d::Event*) 
	{
		return true;
		motion->reset();
		motion->setPosition(touch->getLocation());
		return true;
	};

	listener->onTouchMoved = [motion](cocos2d::Touch* touch, cocos2d::Event*)
	{
		motion->setPosition(touch->getLocation());
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	return;
	//
	m_pRainbow = RibbonTrail::create("ribbontrail.png", 150, 2000);
	if (!m_pRainbow)
		return ;
	m_pRainbow->setPosition3D(Vec3(0, 25, -800));
	m_pRainbow->setCameraMask((unsigned short)CameraFlag::USER1);
	this->addChild(m_pRainbow);
	m_pRainbow->getTrail()->addNode(m_pRainbow);

	m_fTime = 0;
	Vec3 pos = m_pRainbow->getPosition3D();
	Vec3 target = this->getDefaultCamera()->getPosition3D() + Vec3(0, -66, 0);
	m_fDirDist = target - pos;

	_scheduler->schedule(
		[this](float dt) {
			//update
			if (m_pRainbow)
			{
				m_fTime += dt;
				if (m_fTime <= 2.0f)
				{
					Vec3 pos = m_pRainbow->getPosition3D();
					Vec3 target = this->getDefaultCamera()->getPosition3D() + Vec3(0, -66, 0);
					pos = pos + m_fDirDist*dt*0.5f - Vec3(0, cosf(M_PI*(m_fTime - 0.5f)) * 200 * dt, 0);
					m_pRainbow->setPosition3D(pos);
					m_pRainbow->update(dt);
				}
			}
		}, this, 0.1f, false, "ribbon"
	);
}

void LearnScene_2::AboutOutline()
{
	auto sp = Sprite::create("shenjianniukuang.png");
	sp->setPosition(Vec2(360, 640));
	this->addChild(sp);

	auto layerColor = LayerColor::create(Color4B::RED);
	layerColor->setBlendFunc(BlendFunc{ GL_DST_ALPHA, GL_ZERO });
	this->addChild(layerColor);

	auto btn = ui::Button::create("tree2.png");
	//btn->setAnchorPoint(Vec2::ZERO);
	btn->setPosition(Vec2(100, 100));
	//this->addChild(btn);

					sp->setScale(1.f);
					auto render = RenderTexture::create(720, 1280);
					render->clear(0.f, 0.f, 0.f, 0.f);
					render->begin();
					this->visit();
					render->end();
					sp->setScale(1.f);

					cocos2d::Director::getInstance()->getRenderer()->render();

					auto texture = render->getSprite()->getTexture();
					auto outline = Sprite::createWithTexture(texture);
					outline->setFlippedY(true);
					//outline->setAnchorPoint(Vec2::ZERO);
					outline->setPosition(360, 640);

					//inline
					//outline->setBlendFunc(BlendFunc{ GL_ONE_MINUS_DST_COLOR, GL_ZERO });
					//render = RenderTexture::create(720, 1280);
					//render->beginWithClear(0.f, 0.f, 0.f, 0.f);
					//sp->setScale(0.9f);
					//sp->visit();
					//outline->visit();
					//render->end();
					//cocos2d::Director::getInstance()->getRenderer()->render();

					//texture = render->getSprite()->getTexture();
					//outline = Sprite::createWithTexture(texture);
					//outline->setFlippedY(true);
					////outline->setAnchorPoint(Vec2::ZERO);
					//outline->setPosition(360, 640);
					//sp->setScale(1.f);
					//sp->setLocalZOrder(2);
					this->addChild(outline, -1);
					
					layerColor->setVisible(false);
}

void LearnScene_2::AboutShaderOutline()
{
	auto layer = LayerColor::create(Color4B(Color3B::GRAY, 50));
	//this->addChild(layer);

	auto sp = Sprite::create("shenjianniukuang.png");
	sp->setPosition(100, 400);
	this->addChild(sp);

	sp = Sprite::create("shenjianniukuang.png");
	sp->setBlendFunc(BlendFunc::ALPHA_NON_PREMULTIPLIED);
	auto program = GLProgram::createWithFilenames("shader/ccShader_PositionTexture_uColor.vert", "shader/ccShader_PositionTexture_uColor_Glow.frag", "");
	program->use();
	program->setUniformsForBuiltins();
	sp->setGLProgram(program);

	sp->setPosition(100, 200);
	this->addChild(sp);
}

void LearnScene_2::AboutGif()
{
	//std::string name = FileUtils::getInstance()->fullPathForFilename("Gif/g1.gif");
	//GifBase* gif = InstantGif::create(name.c_str());
	//gif->setPosition(320, 480);
	//addChild(gif);

	//CacheGif* gif = CacheGif::create(name.c_str());
	//gif->setPosition(320, 160);
	//addChild(gif);

	//InstantGifData* gif = InstantGifData::create("Gif/g1.gif");
	//gif->setPosition(460, 480);
	//addChild(gif);

	//CacheGifData* gif = CacheGifData::create("Gif/g1.gif");
	//gif->setPosition(460, 160);
	//addChild(gif);

	//GIFMovieData* movie = new GIFMovieData;
	//movie->init("Gif/g1.gif");
	//Sprite* pImg = Sprite::create();
	//pImg->initWithTexture(movie->GetTexture(5));
	//pImg->setPosition(428, 320);
	//addChild(pImg);
	//delete movie;

	//pImg = Sprite::create();
	//pImg->initWithTexture(GIFMovieData::StaticGetTexture("Gif/g1.gif", 0));
	//pImg->setPosition(856, 320);
	//addChild(pImg);
}

void LearnScene_2::AboutWriteXML()
{
	auto btn = ui::Button::create();
	cocos2d::ValueVector vl;
	vl.push_back(Value(1));
	auto path = FileUtils::getInstance()->getWritablePath();
	FileUtils::getInstance()->writeValueVectorToFile(vl, path + "test.xml");
}

void LearnScene_2::putPointIntoCloseList(PointInfo* node)
{
	auto iter = std::find(closeList.begin(), closeList.end(), node);

	if (iter != closeList.end())
	{
		log("ERROR: closeList got it ");
		assert(false);
	}

	auto coordinate = node->coordinate;
	
	this->getChildByTag(coordinate.x * 100 + coordinate.y)->setColor(Color3B::MAGENTA);

	closeList.push_back(node);

	auto iter_open = std::find(openList.begin(), openList.end(), node);
	if (iter_open != openList.end())
	{
		openList.erase(iter_open);
	}

	checkAroundToFindShortestNode(node);
}

void LearnScene_2::checkAroundToFindShortestNode(PointInfo* node)
{
	this->getAroundPointInfo(node);
}

void LearnScene_2::getAroundPointInfo(PointInfo * parent)
{
	bool isOver = false;
	auto coordinate = parent->coordinate;
	auto origin = parent->coordinate - Vec2(1, 1);
	PointInfo* endPoint = nullptr;

	for (auto i = 0; i < 3; i++)
	{
		if (i + origin.x > ROW - 1)
			break;
		if (i + origin.x < 0)
			continue;

		for (auto j = 0; j < 3; j++)
		{
			if (j + origin.y > COLUMN - 1)
				break;
			if (j + origin.y < 0 )
				continue;

			auto curPoint = origin + Vec2(i, j);
			//遍历到自己 跳过
			if (curPoint == coordinate)
				continue;

			if ((curPoint - coordinate).length() > 1.f)
				continue;

			//遍历到障碍 跳过
			auto iter = std::find(obstacle.begin(), obstacle.end(), curPoint);
			if (iter != obstacle.end())
				continue;
			//在封闭空间中跳过
			auto iter_closeList = std::find_if(closeList.begin(), closeList.end(), [&curPoint](PointInfo* info) 
			{
				if (info->coordinate == curPoint)
					return true;
				return false;
			});

			if (iter_closeList != closeList.end())
				continue;
			//如果是终点则不用再进行递归
			if (curPoint == destination)
			{
				isOver = true;
			}
			//如果在开放空间中存在，则比较G是否小一些，如果是，则更新
			auto iter_open = std::find_if(openList.begin(), openList.end(), [&curPoint, parent](PointInfo* node)
			{
				if (node->coordinate == curPoint)
				{
					//check g
					auto diff = parent->coordinate - curPoint;
					//相同则一定为1
					int g = abs(diff.x) == abs(diff.y) ? 14 : 10;

					if (node->g > parent->g + g)
					{
						node->parent = parent;
						node->g = parent->g + g;
					}
					return true;
				}
				return false;
			});

			if (iter_open == openList.end())
			{
				PointInfo* p = new PointInfo();
				p->parent = parent;
				auto diff = parent->coordinate - curPoint;
				int g = abs(diff.x) == abs(diff.y) ? 14 : 10;
				p->g = g + parent->g;
				p->h = abs(curPoint.x - destination.x) * 10 + abs(curPoint.y - destination.y) * 10;
				p->coordinate = curPoint;
				openList.push_back(p);
				this->getChildByTag(curPoint.x * 100 + curPoint.y)->setColor(Color3B::GREEN);
				if (isOver && !endPoint)
				{
					endPoint = p;	
				}
			}
		}
	}

	if (!isOver)
	{
		if (openList.empty())
		{
			log("can't find");
		}
		else
		{
			std::sort(openList.begin(), openList.end(), [](PointInfo* first, PointInfo* second)
			{
				if (first->g + first->h < second->g + second->h)
					return true;
				return false;
			});
			
			this->runAction(Sequence::create(
				DelayTime::create(0.3f),
				CallFunc::create([this]() { 
					putPointIntoCloseList(*openList.begin());  
				}),
				nullptr
			));
		}
	}
	else
	{
		showRoute(endPoint);
	}
}

void LearnScene_2::showRoute(PointInfo * endPoint)
{
	if (endPoint == nullptr)
		return;
	this->getChildByTag(endPoint->coordinate.x * 100 + endPoint->coordinate.y)->setColor(Color3B::ORANGE);
	this->runAction(Sequence::create(
		DelayTime::create(0.1f),
		CallFunc::create([this, endPoint]() { this->showRoute(endPoint->parent); }),
		nullptr
	));
}

P_TransitionScene * P_TransitionScene::create(float t, Scene * scene)
{
	auto pRet = new(std::nothrow) P_TransitionScene();
	pRet->_time = t;
	if (pRet && pRet->initWithDuration(t, scene))
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_RELEASE(pRet);
	return nullptr;
}

#include "ui/UIPageView.h"
void P_TransitionScene::onEnter()
{
	TransitionScene::onEnter();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto layerUp = LayerColor::create(Color4B::WHITE, visibleSize.width, visibleSize.height / 2);
	layerUp->setPosition(0, visibleSize.height);
	this->addChild(layerUp);

	auto layerDown = LayerColor::create(Color4B::WHITE, visibleSize.width, visibleSize.height / 2);
	layerDown->setPosition(0, -visibleSize.height / 2);
	this->addChild(layerDown);

	auto move = MoveBy::create(1.f, Vec2(0, visibleSize.height / 2));
	auto act_up = EaseBounceOut::create(move);
	auto act_down = EaseBounceOut::create(move->reverse());

	layerUp->runAction(Sequence::create(
			act_down,
			DelayTime::create(_time),
			move->clone(),
			CallFunc::create([this]() { this->finish(); }),
			nullptr
		)
	);
	layerDown->runAction(
		Sequence::create(
			act_up,
			DelayTime::create(_time),
			move->reverse(),
			nullptr
		)
	);
}

ticket::ticket()
	:n(10)
{
		std::thread thA(&ticket::myThreadA, this);
		std::thread thB(&ticket::myThreadB, this);
		thA.detach();
		thB.detach();

		cocos2d::log("constructor!");
}

void ticket::myThreadA()
{
	while (true)
	{
		mutex.lock();
		if (n > 0)
		{
			Sleep(100);
			log("A Sell %d", n--);//输出售票，每次减1  
			mutex.unlock();
		}
		else {
			mutex.unlock();
			break;
		}
	}
}

void ticket::myThreadB()
{
	while (true)
	{
		mutex.lock();
		if (n > 0)
		{
			Sleep(100);
			log("B Sell %d", n--);//输出售票，每次减1  
			mutex.unlock();
		}
		else {
			mutex.unlock();
			break;
		}
	}
}

//Track
void TrackPart::move()
{
	auto broPos = _bro->getPosition();
	auto rotation = _bro->getRotation();
	//存放点
	if (_track.empty())
	{
		float offsetX = _distance * cosf(CC_DEGREES_TO_RADIANS(90 - (rotation + 180)));
		float offsetY = _distance * sinf(CC_DEGREES_TO_RADIANS(90 - (rotation + 180)));
		_track.emplace_back(broPos + Vec2(offsetX, offsetY), rotation);
	}
	else
	{
		const std::pair<Vec2, float>& back = _track.back();
		auto length = (back.first - broPos).getLength();
		if (length != _distance)
		{
			refreshTrack({ broPos, rotation });
		}
	}

	_track.emplace_back(broPos, rotation);
}

void TrackPart::refreshTrack(const std::pair<cocos2d::Vec2, float>& broInfo)
{
	std::pair<cocos2d::Vec2, float> compareInfo = broInfo;
	std::deque<std::pair<cocos2d::Vec2, float>> newTrack;
	std::pair<cocos2d::Vec2, float> frontInfo = broInfo;
	std::pair<cocos2d::Vec2, float> backInfo = _track.back();
	std::deque<std::pair<cocos2d::Vec2, float>>::reverse_iterator tag = _track.rbegin();

	for (auto iter = _track.rbegin(); iter != _track.rend(); iter++)
	{
		auto length = (backInfo.first - compareInfo.first).getLength();
		//现有的点与重新规划的点(compareInfo)进行计算，如果原来的点的区域内无与新点有匹配距离(length < _distance)，则向后找点
		while (length < _distance)
		{
			assert(tag != _track.rend());

			frontInfo = *tag;
			tag++;
			if (tag == _track.rend())
				backInfo = { _position, _rotationZ_X };
			else
				backInfo = *tag;
			length = (compareInfo.first - backInfo.first).getLength();
		}

		//获取旧区域内的点与新点距离一致的点(直线与圆相交)
		if (length == _distance)
		{
			compareInfo = backInfo;
			newTrack.push_front(compareInfo);
		}
		else if (length > _distance)
		{
			//line
			auto k = (backInfo.first.y - frontInfo.first.x) / (backInfo.first.x - frontInfo.first.x);
			auto b = backInfo.first.y - k * backInfo.first.x;
			
			auto pointC = compareInfo.first;

			auto a = 1 + k * k;
			auto b1 = 2 * (k * b - k * pointC.y - pointC.x);
			auto c = pointC.x * pointC.x + (b - pointC.y) * (b - pointC.y) - _distance * _distance;

			auto x1 = (-b1 + sqrt(b1 * b1 - 4 * a * c)) / 2 * a;
			auto x2 = (-b1 - sqrt(b1 * b1 - 4 * a * c)) / 2 * a;
			float x;
			float dis = -1;
			if (backInfo.first.x > frontInfo.first.x)
			{
				if (x1 >= frontInfo.first.x && x1 <= backInfo.first.x)
				{
					dis = backInfo.first.x - x1;
					x = x1;
				}

				if (x2 >= frontInfo.first.x && x2 <= backInfo.first.x)
				{
					if (dis > backInfo.first.x - x2)
					{
						dis = backInfo.first.x - x2;
						x = x2;
					}
				}
			}
			else
			{
				if (x1 >= backInfo.first.x && x1 <= frontInfo.first.x)
				{
					dis = x1 - backInfo.first.x;
					x = x1;
				}

				if (x2 >= backInfo.first.x && x2 <= frontInfo.first.x)
				{
					if (dis > x2 - backInfo.first.x)
					{
						dis = x2 - backInfo.first.x;
						x = x2;
					}
				}
			}
			float y = k * x + b;
			assert(dis != -1);
			float rotation = frontInfo.second + (backInfo.second - frontInfo.second) * (1 - dis / abs(backInfo.first.x - frontInfo.first.x));
			compareInfo = { Vec2(x, y), rotation };
			newTrack.push_front(compareInfo);
		}
	}

	_track.swap(newTrack);
}
