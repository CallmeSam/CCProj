#include "TwoSceneTest.h"
#include "ui\UIWidget.h"
#include "cocostudio\CocoStudio.h"

USING_NS_CC;



class OldSteel
{
public :
	OldSteel() :a(2) {}
	
	virtual int* kiddingMe() { return &a; }
	virtual const int kiddingMe() const { log("%d", a);  return 2; }
private:
	int a;
};

void FirstScene::AboutParent()
{
	Node* node = Node::create();
	node->setPosition(Vec2(100, 100));
	node->runAction(MoveBy::create(10.0f, Vec2(500, 0)));
	addChild(node);

	auto no = Node::create();
	addChild(no);

	Sprite* sp = Sprite::create("CloseNormal.png");
	log("%f--%f", sp->getPositionX(), sp->getPositionY());
	node->addChild(sp);

	this->runAction(Sequence::createWithTwoActions(
		DelayTime::create(3.0f),
		CallFunc::create([sp, no]() {
				//不能这么用！！！！！
				sp->setParent(no); 
				sp->removeFromParent();
				log("%f--%f", sp->getPositionX(), sp->getPositionY());
			})
	));
}

void FirstScene::AboutScheduleLamda()
{
	this->schedule([](float dt) {log("haha"); }, "first");
}

void FirstScene::AboutConvert()
{
	Sprite* sp = Sprite::create("CloseNormal.png");
	addChild(sp);

	Vec2 constant(100, 100);
	Vec2 pos = sp->convertToNodeSpace(constant);

	log("--%f--%f", sp->getContentSize().width, sp->getContentSize().height);
	log("--%f--%f", pos.x, pos.y);
	
	pos = sp->convertToNodeSpaceAR(constant);
	log("--%f--%f", pos.x, pos.y);

	pos = sp->convertToWorldSpace(constant);
	log("--%f--%f", pos.x, pos.y);

	pos = sp->convertToWorldSpaceAR(constant);
	log("--%f--%f", pos.x, pos.y);
}

void FirstScene::AboutOpacity()
{
	auto sp = Sprite::create("CloseNormal.png");
	sp->setCascadeOpacityEnabled(true);
	addChild(sp);

	log("_realOpacity %d", sp->getOpacity() - '\0');
	log("_displayedOpacity %d", sp->getDisplayedOpacity() - '\0');

	auto s_p = Sprite::create("CloseNormal.png");
	s_p->setPosition(Vec2(200, 200));
	sp->addChild(s_p);

	sp->setOpacity(220);

	log("_realOpacity %d", s_p->getOpacity() - '\0');
	log("_displayedOpacity %d", s_p->getDisplayedOpacity() - '\0');

	
}

void FirstScene::AboutEmptyTexture()
{
	Sprite* sp = Sprite::create();
	sp->setPosition(Vec2(200, 200));
	addChild(sp);

	//just read sound code sprite.cpp  
	//rotated. offset. _unflipsetPositionFromCenter
	SpriteFrameCache::getInstance()->addSpriteFrame(
		SpriteFrame::create("CloseNormal.png", Rect(0, 0, 40, 40), true, Vec2(50, 50), Size(40, 40)),
		"frame"
	);
	
	SpriteFrameCache::getInstance()->addSpriteFrame(
		SpriteFrame::create("CloseNormal.png", Rect(0, 0, 40, 40), true, Vec2::ZERO, Size(20, 20)),
		"frame_2"
	);

	sp = Sprite::createWithSpriteFrameName("frame");
	sp->setFlippedY(true);
	sp->setAnchorPoint(Vec2::ZERO);
	sp->setPosition(Vec2(200, 200));
	//sp->debugDraw(true);
	addChild(sp);

	sp = Sprite::createWithSpriteFrameName("frame");
	sp->setFlippedY(true);
	sp->setPosition(Vec2(200, 200));
	//sp->debugDraw(true);
	addChild(sp);

	sp = Sprite::createWithSpriteFrameName("frame_2");
	//sp->debugDraw(true);
	sp->setPosition(Vec2(200, 200));
	sp->runAction(MoveBy::create(10.0f, Vec2(1000, 0)));
	addChild(sp);
}

void FirstScene::AboutLayer()
{
	Layer* layer = Layer::create();
	//改变anchorPoint对child并没有什么影响，因为开启了_ignoreAnchorPointForPosition，
	layer->setAnchorPoint(Vec2(0, 1));
	addChild(layer);

	Node* node = Node::create();
	layer->addChild(node);
	node->setContentSize(Size(100, 100));
	node->setRotation(40);

	this->runAction(Sequence::createWithTwoActions(
			DelayTime::create(1.0f),
			CallFunc::create([node]() {
			log("%f--%f", node->getBoundingBox().size.width, node->getBoundingBox().size.height);
			log("%f", node->getRotation());
		})
	));
	
}

class OldLayer : public Layer
{
public:
	CREATE_FUNC(OldLayer);
	virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
	{
		log("click!!");
	}
};

void FirstScene::AboutLayerSetTouchEnable()
{
	OldLayer* layer = OldLayer::create();
	layer->setTouchEnabled(true);
	addChild(layer);

	//auto otherLayerColor = LayerGradient::create(Color4B::BLUE, Color4B::MAGENTA, Vec2(1, 1));
	//addChild(otherLayerColor);
}

#undef CC_PROFILER_DISPLAY_TIMERS
#define CC_PROFILER_DISPLAY_TIMERS() Profiler::getInstance()->displayTimers()
void FirstScene::AboutTimelineEfficiency()
{

	
	FileUtils::getInstance()->addSearchPath("externRec");

	//Profiler::getInstance()->createAndAddTimerWithName("timeline");

	auto node = CSLoader::createNode("LayerUI.csb");
	addChild(node);
	//auto timeline = CSLoader::createTimeline("zombie.csb");
	//auto node = CSLoader::createNode("zombie.csb");

	CC_PROFILER_START("timeline");
	//for (int i = 0; i < 20; i++)
	//{
	//	auto node = CSLoader::createNode("zombie.csb");
	//	//auto timeline = CSLoader::createTimeline("zombie.csb");
	//	timeline->clone();
	//}

	//node->runAction(timeline);
	//timeline->gotoFrameAndPlay(0);
	//node->retain();

	//this->runAction(Sequence::createWithTwoActions(DelayTime::create(1.0f), CallFunc::create([=]() {this->addChild(node); node->release(); })));

	//Profiler::getInstance()->displayTimers();
	CC_PROFILER_STOP("timeline");

	CC_PROFILER_DISPLAY_TIMERS();
}

struct pathTrack
{
public:
	void describe()
	{
		printf("coord : (%.1f, %.1f)\n G: %.1f \n H: %d\n F: %.1f \n", coord.x, coord.y, G, H, F);
	}

public:
	Vec2 coord;
	float G;
	int H;
	float F;
	pathTrack* father;
};

//uncomplete
void FirstScene::AboutAStarPath()
{
	//1起点，2障碍，3中点
	int pathData[7][5] =
	{
		{ 0, 0, 0, 0, 0 },
		{ 0, 0, 1, 0, 0 },
		{ 0, 0, 0, 0, 0 },
		{ 0, 2, 2, 2, 0 },
		{ 0, 0, 0, 0, 0 },
		{ 0, 0, 3, 0, 0 },
		{ 0, 0, 0, 0, 0 },
	};

	Vec2 startPos = Vec2(1, 2);
	Vec2 endPos = Vec2(5, 2);
	pathTrack *parent = new pathTrack();

	std::vector<pathTrack*> closeList;
	std::vector<pathTrack*> openList;

	//不严谨
	float minF = 100.0f;
	for (int i = -1; i <= 1; i++)
		for(int j = -1; j <= 1; j++)
	{
			Vec2 curPos = startPos + Vec2(i, j);
			if (curPos != startPos && curPos.x >= 0 && curPos.y >= 0)
			{
				pathTrack* track = new pathTrack();
				track->coord = curPos;
				track->father = parent;
				track->G = sqrt(pow(startPos.x - curPos.x, 2) + pow(startPos.y - curPos.y, 2));
				track->H = abs(endPos.x - curPos.x) + abs(endPos.y - curPos.y);
				track->F = track->G + track->H;
				//minF = track->F < minF
				track->describe();
				openList.push_back(track);
			}
	}


	for (auto child : openList)
	{
		CC_SAFE_DELETE(child);
	}

	openList.clear();
}

//总结：会根据sp的位置
void FirstScene::AboutClippingNodePos()
{
	auto sp = Sprite::create("HelloWorld.png");
	sp->setPosition(Vec2(240, 400));

	auto clip = ClippingNode::create();
	clip->setStencil(sp);
	addChild(clip);

	clip->setAlphaThreshold(0.5f);

	auto sp_2 = Sprite::create("HelloWorld.png");
	sp_2->setPosition(Vec2(240, 400));
	clip->addChild(sp_2);
}

void FirstScene::visit(cocos2d::Renderer * render, const cocos2d::Mat4 & parentTransform, std::uint32_t parentFlags)
{
	Scene::visit(render, parentTransform, parentFlags);
	_command.init(_globalZOrder);
	_command.func = CC_CALLBACK_0(FirstScene::onDraw, this);
	Director::getInstance()->getRenderer()->addCommand(&_command);
}

void FirstScene::onDraw()
{
	//获得当前shader
	auto glProgram = getGLProgram();
	//使用此shader
	glProgram->use();
	//设置该shader的一些内置uniform,主要是mvp,即model-view-project矩阵
	glProgram->setUniformsForBuiltins();

	auto size = Director::getInstance()->getWinSize();

	float vertices[] = {
		0, 0,
		size.width, 0, 
		size.width / 2, size.height
	};

	float color[] = {
		0, 1, 0, 1,
		1, 0, 0, 1,
		0, 0, 1, 1, 
	};

	GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR);
	//分别给position和color指定数据源
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, color);
	//绘制三角形，所谓的draw call就是指这个函数调用
	glDrawArrays(GL_TRIANGLES, 0, 3);
	//通知cocos2d-x的renderer，让它在合适的时候调用这些opengl命令
	CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 3);
	//如果出错了，可是使用这个函数来获取出错信息
	CHECK_GL_ERROR_DEBUG();
}


bool FirstScene::init()
{
	if (!Scene::init())
		return false;

	Layer* layer = Layer::create();
	addChild(layer);

	//Node* node = Node::create();
	//layer->addChild(node);

	//ui::Widget* widget = ui::Widget::create();
	//widget->setTouchEnabled(true);
	//widget->setContentSize(Size(200, 200));
	//widget->addTouchEventListener([](Ref*, ui::Widget::TouchEventType type) { if (type == ui::Widget::TouchEventType::ENDED)
	//		Director::getInstance()->replaceScene(SecondScene::create());
	//		log("haha");
	//	});
	//layer->addChild(widget);

	//this->runAction(Sequence::create(
	//			DelayTime::create(3.0f),
	//			CallFunc::create([this]() 
	//				{
	//					this->addChild(Node::create());
	//				}),
	//			nullptr
	//));

	//virtual const
	/*OldSteel* a = new OldSteel();
	CC_SAFE_DELETE(a);

	const OldSteel* b = new OldSteel();
	auto p = b->kiddingMe();
	log("%d", p);
	CC_SAFE_DELETE(b);*/

	//AboutParent();
	//AboutScheduleLamda();
	//AboutConvert();

	//AboutOpacity();

	//AboutEmptyTexture();

	//AboutLayer();

	//AboutLayerSetTouchEnable();

	//AboutTimelineEfficiency();

	//AboutAStarPath();

	//AboutClippingNodePos();

	//AboutShader
	this->setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_COLOR));

	return true;
}

bool SecondScene::init()
{
	if (!Scene::init())
		return false;

	return true;
}
