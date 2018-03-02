#include "HelloWorldScene.h"

#include "ui\UIButton.h"
#include "Box2D\Box2D.h"

USING_NS_CC;
USING_NS_CC_EXT;

using namespace cocostudio::timeline;
Size visibleSize;
Vec2 visibleOrigin;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    //auto scene = Scene::create();
    
	auto scene = Scene::createWithPhysics();

	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2::ZERO);

    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
	layer->_world = scene;
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	_actionManager = nullptr;
   visibleSize = Director::getInstance()->getVisibleSize();
    visibleOrigin = Director::getInstance()->getVisibleOrigin();
	_drawNode = nullptr;
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(visibleOrigin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
		visibleOrigin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(visibleOrigin.x + visibleSize.width/2,
		visibleOrigin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    //// add "HelloWorld" splash screen"
    //auto sprite = Sprite::create("HelloWorld.png");

    //// position the sprite on the center of the screen
    //sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    //// add the sprite as a child to this layer
    //this->addChild(sprite, 0);
    
	//初始化完了物理场景
	initPhysical();

	//添加素材
	//auto parent = Sprite::create("CloseNormal.png");
	//this->addChild(parent, 0, 10);

	//clippingNode
	//AboutClippingNode();
	//AbooutActionManager();
	//AboutEffect();
	//AboutTableView();
	//AboutTimeline();

	/*ValueVector vec = FileUtils::getInstance()->getValueVectorFromFile("456.xml");
	std::string str = vec.at(1).asString();*/

	//Label* lb = Label::createWithSystemFont(str, "微软雅黑", 30);
	//lb->setPosition(visibleSize / 2);
	//addChild(lb);

	//AboutFileUtils();
	//revise
	//AboutCaptureScreen();

	//强枚举类型
	//auto a = Colour::RED;

	//AboutLabel();

	//AboutCascade();

	//AboutCocosPhysical();
	//AboutRendering();
	//AboutTexturePart();
	//AboutRenderTextureNode();
	//AboutWildPointer();
    
	//AboutAutoPolygon();
	//AboutFastTileMap();
	//去看实例
	//AboutTextField();
	//性能测试
	//AboutProfilerDisplay();
	//AboutClippingNodeAgain();
	//AboutParticles();

	return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::initPhysical()
{
	/*
	_space = cpSpaceNew();
	_space->gravity = cpv(0, -100);

	_walls[0] = cpSegmentShapeNew(_space->staticBody, cpv(0, 0), cpv(visibleSize.width, 0), 0.0f);
	_walls[1] = cpSegmentShapeNew(_space->staticBody, cpv(0, visibleSize.height), cpv(visibleSize.width, visibleSize.height), 0.0f);
	_walls[2] = cpSegmentShapeNew(_space->staticBody, cpv(0, 0), cpv(0, visibleSize.height), 0.0f);
	_walls[3] = cpSegmentShapeNew(_space->staticBody, cpv(visibleSize.width, 0), cpv(visibleSize.width, visibleSize.height), 0.0f);

	for (int i = 0; i < 4; i++)
	{
		_walls[i]->e = 1.0f;
		_walls[i]->u = 1.0f;
		auto shape = cpSpaceAddShape(_space, _walls[i]);
		
		//cpSpaceAddStaticShape(_space, _walls[i]);
	}

	//physics debug layer
	_debugLayer = PhysicsDebugNode::create(_space);
	this->addChild(_debugLayer, 100);

	int num = 4;
	cpVect verts[] = {
		cpv(-20, -20),
		cpv(-20, 20),
		cpv(20, 20),
		cpv(20, -20)
	};

	cpBody* body = cpBodyNew(1.0f, cpMomentForPoly(1.0f, num, verts, cpvzero));
	body->p = cpv(visibleSize.width / 2, visibleSize.height / 2);
	cpSpaceAddBody(_space, body);
	cpShape* shape = cpPolyShapeNew(body, num, verts, cpvzero);
	shape->e = 0.5f;
	shape->u = 0.5f;
	cpSpaceAddShape(_space, shape);
	
	auto sprite = PhysicsSprite::create("CloseNormal.png");
	this->addChild(sprite);

	sprite->setCPBody(body);
	sprite->setPosition(visibleSize / 2);

	scheduleUpdate();
	*/

	auto edge = Node::create();
	edge->addComponent(PhysicsBody::createEdgeSegment(Vec2::ZERO, Vec2(960, 0)));
	addChild(edge);
	auto visibleSize = Director::getInstance()->getVisibleSize();

	for (auto i = 0; i < 200; i++)
	{
		auto phy = Sprite::create("one_arrow.png");
		phy->setPosition(visibleSize.width * rand_0_1(), visibleSize.height * rand_0_1());
		auto physicsBody = PhysicsBody::createBox(phy->getContentSize());
		physicsBody->setCategoryBitmask(1);
		physicsBody->setCollisionBitmask(2);
		phy->addComponent(physicsBody);
		addChild(phy);
	}

	for (auto j = 0; j < 100; j++)
	{
		auto phy = Sprite::create("paw.png");
		phy->setPosition(visibleSize.width * rand_0_1(), visibleSize.height * rand_0_1());
		auto physicsBody = PhysicsBody::createBox(phy->getContentSize());
		physicsBody->setCategoryBitmask(2);
		physicsBody->setCollisionBitmask(1);
		phy->addComponent(physicsBody);
		addChild(phy);
	}
}

void HelloWorld::update(float delta)
{
	//physical world
	//int steps = 2;
	//float dt = Director::getInstance()->getAnimationInterval() / (float)steps;
	//for (int i = 0; i < steps; i++)
	//{
	//	cpSpaceStep(_space, dt);
	//}

	//CocosPhysicsWorld
	//int steps = 2;
	//float dt = Director::getInstance()->getAnimationInterval() / (float)steps;
	//for (int i = 0; i < steps; i++)
	//{
	//	_world->getPhysicsWorld()->step(dt);
	//}
	//for (int i = 0; i < 3; ++i)
	//{
	//	_world->getPhysicsWorld()->step(1 / 180.0f);
	//}
}

void HelloWorld::AboutClippingNode()
{
	ClippingNode* clippingNode = ClippingNode::create();
	Sprite* sp = Sprite::create("CloseNormal.png");
	Sprite* stencil = Sprite::create();
	stencil->setContentSize(Size(40, 40));
	clippingNode->setStencil(sp);
	log("stencil  width:%f----height:%f", sp->getContentSize().width, sp->getContentSize().height);
	addChild(clippingNode);
	log("clippingNode width:%f--height:%f\n posX:%f--posY:%f", clippingNode->getContentSize().width, clippingNode->getContentSize().height, clippingNode->getPositionX(), clippingNode->getPositionY());
	Sprite* bg = Sprite::create("HelloWorld.png");
	clippingNode->addChild(bg);
	clippingNode->setInverted(true);
	clippingNode->setAlphaThreshold(0.5);
	clippingNode->setPosition(visibleSize / 2);
}

void HelloWorld::AbooutActionManager()
{
	
	_actionManager = new(std::nothrow) ActionManager();
	Director::getInstance()->getScheduler()->scheduleUpdate(_actionManager, Scheduler::PRIORITY_SYSTEM, false);
	Sprite* sp = Sprite::create("HelloWorld.png");
	sp->setPosition(visibleSize / 2);
	addChild(sp);
	sp->setActionManager(_actionManager);

	Action* act = MoveBy::create(3.0, Vec2(100, 0));
	act->setTag(1);
	sp->runAction(act);

	Action* act2 = RotateBy::create(2.0, 90.0f);
	act2->setTag(2);
	_actionManager->addAction(act2, sp, false);

	ui::Button* btn = ui::Button::create("CloseNormal.png", "CloseNormal.png", "CloseNormal");
	addChild(btn);
	//btn->runAction(act2);
	btn->setPosition(Vec2(50, 100));

	log("%d", _actionManager->getNumberOfRunningActionsInTarget(sp));
	log("%d", _actionManager->getNumberOfRunningActionsInTarget(sp));

	Action* ac = sp->getActionManager()->getActionByTag(2, sp);
	if (ac)
		log("yeah!");
	else
		log("noop!");
	btn->addTouchEventListener([&](Ref*, ui::Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			_actionManager->pauseTarget(sp);
		}
	});
}

void HelloWorld::AboutFileUtils()
{
	//转UTF-8
	ValueMap map = FileUtils::getInstance()->getValueMapFromFile("123.xml");
	
	map["No.2"] = "rocket";
	std::string str = map["No.2"].asString();
	log("value:%s", str.c_str());

	auto instance = FileUtils::getInstance();
	instance->addSearchPath("lookat");
	instance->addSearchResolutionsOrder("deepInside", true);

	ValueMap map2;
	map2["400.png"] = "4000.png";
	instance->setFilenameLookupDictionary(map2);
	log("dictionary:%s", instance->fullPathForFilename("400.png").c_str());


	log("%d", instance->isFileExist("4000.png"));
	auto searchPaths = instance->getSearchResolutionsOrder();
	for (auto iter = searchPaths.begin(); iter != searchPaths.end(); iter++)
		log("searchPath:%s", (*iter).c_str());

	log("writePath:%s", instance->getWritablePath().c_str());
}

void HelloWorld::AboutEffect()
{
	auto nodeGrid = NodeGrid::create();
	Sprite*  sp = Sprite::create("HelloWorld.png");
	sp->setPosition(visibleSize / 2);
	
	Action* act1 = Lens3D::create(3.0f, Size(32, 24), visibleSize / 2, 300);
	//最后一个参数幅度
	auto act2 = Waves3D::create(3.0f, Size(32, 24), 10, 15);
	//顺序执行动作时，在前面运行效果的基础上运行下一个效果，前面运行的效果还保持着。
	auto act3 = ReuseGrid::create(1);
	auto act4 = Sequence::create(act2, act1, act3,  nullptr);
	//分成块
	auto act5 = ShakyTiles3D::create(3.0f, Size(15, 10), 10, false);
	//不分块
	auto act6 = Shaky3D::create(3.0f, Size(15, 10), 10, false);
	//洗牌
	auto act7 = ShuffleTiles::create(1.0f, Size(15, 10), 10);
	//方块消失特效
	auto act8 = TurnOffTiles::create(3.0, Size(15, 10));
	auto act9 = act8->reverse();
	auto act10 = Sequence::create(act8, act9, nullptr);
	auto act11 = Liquid::create(3.f, Size(15, 10), 10, 10);
	auto act12 = StopGrid::create();
	auto act13 = Sequence::create(act11, DelayTime::create(3.0f), act12, nullptr);
	auto act14 = FlipX3D::create(3.0f);
	auto act15 = FlipY3D::create(3.0f);
	//起伏，细浪
	auto act16 = Ripple3D::create(3.0f, Size(15, 10), visibleSize / 2, 200, 10, 10);
	auto act17 = Waves::create(3.0f, Size(15, 10), 10, 10, true, false);
	auto act18 = Twirl::create(3.0f, Size(15, 10), visibleSize / 2, 5, 1);
	auto act19 = ShatteredTiles3D::create(15.0f, Size(15, 10), 10, false);
	//右上角开始消失
	auto act20 = FadeOutBLTiles::create(3.0, Size(15, 10));
	//左下角开始消失
	auto act21 = FadeOutTRTiles::create(3.0, Size(15, 10));
	auto act22 = FadeOutDownTiles::create(3.0, Size(15, 10));
	auto act23 = FadeOutUpTiles::create(3.0, Size(15, 10));
	auto act24 = JumpTiles3D::create(3.0, Size(15, 10), 5, 10);
	auto act25 = SplitRows::create(3.0, 10);
	auto act26 = SplitCols::create(3.0, 10);
	auto act27 = PageTurn3D::create(3.0, Size(15, 10));
	nodeGrid->runAction(act27);
	
	nodeGrid->setAnchorPoint(Vec2(0.5, 0.5));
	nodeGrid->addChild(sp);
	addChild(nodeGrid);
}

void HelloWorld::AboutTableView()
{
	TableView* tableView = TableView::create(this, Size(250, 60));
	tableView->setDirection(ScrollView::Direction::HORIZONTAL);
	tableView->setPosition(Vec2(60, visibleSize.height / 2 - 50));
	//设置回掉响应的
	tableView->setDelegate(this);
	//排序是按照19-0 还是0-19 好像只能适用于VERTICAL
	//tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	this->addChild(tableView);
	tableView->reloadData();
}

void HelloWorld::AboutTimeline()
{
	Node* node = CSLoader::createNode("Scene.csb");
	addChild(node);

	auto action = CSLoader::createTimeline("Scene.csb");
	action->gotoFrameAndPlay(0, false);

	node->runAction(action);
	std::function<void(cocostudio::timeline::Frame*)> st;
	st = std::bind(&HelloWorld::timelineCallback, this, std::placeholders::_1);
	//st = &HelloWorld::timelineCallback;
	action->setFrameEventCallFunc(st);
}

void HelloWorld::AboutCaptureScreen()
{
	Sprite* spb = Sprite::create("CloseNormal.png");
	spb->setPosition(visibleSize / 2);
	auto clippingNode = ClippingNode::create(spb);
	addChild(clippingNode);

	Sprite* sd = Sprite::create("HelloWorld.png");
	sd->runAction(MoveTo::create(5.0f, Vec2(400, 0)));
	//sd->setPosition(visibleSize / 2);
	addChild(sd);
	sd->setGlobalZOrder(-1);


	Sprite* sp = Sprite::create("HelloWorld.png");
	sp->setPosition(visibleSize / 2);
	clippingNode->addChild(sp);
	utils::captureScreen(CC_CALLBACK_2(HelloWorld::afterCapture, this), "c1aptrue.png");

	this->runAction(Sequence::create(DelayTime::create(5.0f), 
		CallFunc::create([&]() {
		const std::string str = FileUtils::getInstance()->getWritablePath() + "c1aptrue.png";
		Director::getInstance()->getTextureCache()->removeTextureForKey(str);
		utils::captureScreen(CC_CALLBACK_2(HelloWorld::afterCapture, this), "c1aptrue.png");
	}), nullptr));
}

void HelloWorld::afterCapture(bool succeed, const std::string & str)
{
	if (succeed)
	{
		log("%s", str.c_str());
		Sprite* sp = Sprite::create(str);
		sp->setPosition(visibleSize / 2);
		sp->setColor(Color3B::BLUE);
		sp->setOpacity(150);
		addChild(sp);
	}
}

void HelloWorld::timelineCallback(cocostudio::timeline::Frame *evnt)
{
	EventFrame* evt = dynamic_cast<EventFrame*>(evnt);
	//((Node*)evnt)->getUserObject()
	if (evt->getEvent() == "try")
	{
		log("123");
	}
}

void HelloWorld::AboutLabel()
{
	auto layerColor = LayerColor::create(Color4B::BLACK, visibleSize.width, visibleSize.height);
	addChild(layerColor);

	//这种方法依然无法读取中字，但是可以放在cocosStudio上
	Label* label = Label::createWithBMFont("123123.fnt", "123");
	label->setColor(Color3B::RED);
	label->setPosition(visibleSize / 2);
	layerColor->addChild(label);
}

void HelloWorld::AboutCascade()
{
	Layer* layer = Layer::create();
	addChild(layer);

	layer->setCascadeOpacityEnabled(true);
	layer->setCascadeColorEnabled(true);
	layer->runAction(FadeTo::create(1, 10));
	layer->runAction(TintTo::create(1, Color3B::RED));
	 
	Sprite* sp = Sprite::create("HelloWorld.png");
	sp->ignoreAnchorPointForPosition(false);
	layer->addChild(sp);
	log("%f--%f", visibleSize.width, visibleSize.height);
	log("origin:%f--%f", visibleOrigin.x, visibleOrigin.y);
	sp->setPosition(visibleSize / 2);

	Sprite* sm_sp = Sprite::create("CloseSelected.png");
	sp->addChild(sm_sp);

	auto limit = DrawNode::create();
	limit->setPosition(Vec2(visibleOrigin.x + 1, visibleOrigin.y + 1));
	limit->drawRect(Vec2(0, 0), Vec2(visibleSize.width - 2, visibleSize.height - 2), Color4F(1, 1, 0, 1));
	//addChild(limit);

}

void HelloWorld::AboutCocosPhysical()
{
	//((Scene*)this->getParent())->initWithPhysics();
	
	Sprite* sp = Sprite::create("CloseSelected.png");
	sp->setPosition(Vec2(30, 30));
	auto spBody = PhysicsBody::createBox(sp->getContentSize());
	spBody->setVelocity(Vect(100, 0));
	log("%f", spBody->getLinearDamping());
	sp->setPhysicsBody(spBody);

	Node* node = Node::create();
	node->setPosition(visibleSize / 2);
	node->setPhysicsBody(PhysicsBody::createEdgeBox(visibleSize));
	addChild(node);

	auto rope = Node::create();
	Vec2 points[] =
	{
		Vec2(0, 0),
		Vec2(visibleSize.width / 2, 0),
		Vec2(visibleSize.width, visibleSize.height / 6)
	};
	rope->setPhysicsBody(PhysicsBody::createEdgeChain(points, 3));
	log("%f", rope->getPhysicsBody()->getLinearDamping());
	rope->setPositionY(rope->getPositionY() + 10);
	addChild(rope);
	//rope->runAction(MoveBy::create(10.0, Vec2(-100, 0)));
	this->addChild(sp);
	//scheduleUpdate();
}

void HelloWorld::AboutRendering()
{
	target = RenderTexture::create(visibleSize.width, visibleSize.height, Texture2D::PixelFormat::RGBA8888);
	target->retain();
	target->setPosition(visibleSize / 2);
	this->addChild(target, -1);

	auto listener = EventListenerTouchAllAtOnce::create();
	
	listener->onTouchesMoved = [this](const std::vector<Touch*>& touches, Event* event) {
		auto touch = touches[0];
		auto start = touch->getLocation();
		auto end = touch->getPreviousLocation();

		//begin drawing
		this->target->begin();
		

		float distance = start.getDistance(end);
		if (distance > 1)
		{
			int d = (int)distance;
			this->_brushs.clear();
			for (int i = 0; i < d; ++i)
			{
				Sprite* sprite = Sprite::create("fire.png");
				sprite->setColor(Color3B::RED);
				sprite->setOpacity(20);
				this->_brushs.pushBack(sprite);
			}
			for (int i = 0; i < d; i++)
			{
				float difx = end.x - start.x;
				float dify = end.y - start.y;
				float delta = (float)i / distance;
				this->_brushs.at(i)->setPosition(Vec2(start.x + (difx * delta), start.y + (dify * delta)));
				this->_brushs.at(i)->setRotation(rand() % 360);
				float r = (float)(rand() % 50 / 50.0f) + 0.25f;
				this->_brushs.at(i)->setScale(r);
				// Use CCRANDOM_0_1() will cause error when loading libtests.so on android, I don't know why.
				this->_brushs.at(i)->setColor(Color3B(rand() % 127 + 128, 255, 255));
				// Call visit to draw the brush, don't call draw..
				this->_brushs.at(i)->visit();
			}
		}
		this->target->end();

	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	
	MenuItemFont *item = MenuItemFont::create("save Image", CC_CALLBACK_1(HelloWorld::saveImage, this));
	MenuItemFont *item2 = MenuItemFont::create("clear Image", CC_CALLBACK_1(HelloWorld::clearImage, this));
	//item->setPosition(Vec2(visibleSize.width - 50, visibleSize.height - 50));
	auto menu = Menu::create(item, item2, nullptr);
	menu->alignItemsHorizontally();
	addChild(menu);
}

HelloWorld::~HelloWorld()
{
	if(_actionManager)
		_actionManager->release();
	if (target)
		target->release();
}

void HelloWorld::tableCellTouched(cocos2d::extension::TableView * table, cocos2d::extension::TableViewCell * cell)
{
	CCLOG("cell touched at index %ld", cell->getIdx());
}

ssize_t HelloWorld::numberOfCellsInTableView(cocos2d::extension::TableView * table)
{
	return 20;
}

cocos2d::Size HelloWorld::tableCellSizeForIndex(cocos2d::extension::TableView * table, ssize_t idx)
{
	if (idx == 0)
	{
		return Size(100, 100);
	}
	return Size(60, 60);
}

cocos2d::extension::TableViewCell * HelloWorld::tableCellAtIndex(cocos2d::extension::TableView * table, ssize_t idx)
{
	const char* str = String::createWithFormat("No.%d", idx)->getCString();
	TableViewCell* cell = table->dequeueCell();
	if (!cell)
	{
		cell = TableViewCell::create();
		Sprite* sp = Sprite::create("CloseNormal.png");
		sp->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		sp->setPosition(Vec2::ZERO);
		cell->addChild(sp, 1, 1);

		auto label = Label::createWithSystemFont(str, "Arial", 20.0);
		label->setPosition(Vec2::ZERO);
		label->setAnchorPoint(Vec2::ZERO);
		cell->addChild(label, 0, 2);
	}
	else
	{
		auto label = (Label*)cell->getChildByTag(2);
		label->setString(str);
	}


	return cell;
}

void HelloWorld::tableCellHighlight(cocos2d::extension::TableView * table, cocos2d::extension::TableViewCell * cell)
{
	Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("CloseSelected.png");
	Sprite* sp = (Sprite*)cell->getChildByTag(1);
	sp->setTexture(texture);
}

void HelloWorld::tableCellUnhighlight(cocos2d::extension::TableView * table, cocos2d::extension::TableViewCell * cell)
{
	Texture2D* texture = TextureCache::getInstance()->addImage("CloseNormal.png");
	Sprite* sp = (Sprite*)cell->getChildByTag(1);
	sp->setTexture(texture);
}

void HelloWorld::onClickTrackNode(bool bClicked)
{
	log("click it!");
	auto pTextField = (TextFieldTTF*)_trackNode;
	if (bClicked)
	{
		pTextField->attachWithIME();
	}
	else
	{
		pTextField->detachWithIME();
	}
}

void HelloWorld::saveImage(cocos2d::Ref* ref)
{
	static int counter = 0;

	char png[20];
	sprintf(png, "image-%d.png", counter);

	auto callback = [&](RenderTexture* rt, const std::string& path)
	{
		auto sprite = Sprite::create(path);
		addChild(sprite);
		sprite->setScale(0.3f);
		sprite->setPosition(Vec2(40, 40));
		sprite->setRotation(3*counter);
	};
	this->target->saveToFile(png, Image::Format::PNG, true, callback);
	//Add this function to avoid crash if we switch to a new scene.
	Director::getInstance()->getRenderer()->render();
	
	counter++;
}

void HelloWorld::clearImage(cocos2d::Ref * ref)
{
	target->clear(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1());
}

//抓取部分屏幕
void HelloWorld::AboutTexturePart()
{
	Sprite* sp = Sprite::create("HelloWorld.png");
	sp->setPosition(visibleSize / 2);
	addChild(sp);

	_drawNode = DrawNode::create();
	addChild(_drawNode);

	RenderTexture* rd = RenderTexture::create(200, 200, Texture2D::PixelFormat::RGBA8888);
	//rd->retain();
	rd->setKeepMatrix(true);
	Size pixelSize = Director::getInstance()->getWinSizeInPixels();
	rd->setVirtualViewport(Size(visibleSize.width / 2 - 100, visibleSize.height / 2 - 100),
		Rect(0, 0, visibleSize.width, visibleSize.height), Rect(0, 0, pixelSize.width, pixelSize.height));

	_drawNode->drawRect(Vec2(visibleSize.width / 2 - 100, visibleSize.height / 2 - 100), Vec2(visibleSize.width / 2 + 100, visibleSize.height / 2 + 100), Color4F::BLUE);
	rd->beginWithClear(1, 0, 0, 1);
	sp->visit();
	rd->end();

	Sprite* sp_texture = Sprite::createWithTexture(rd->getSprite()->getTexture());
	sp_texture->setFlippedY(true);
	sp_texture->setPosition(visibleSize / 2);
	sp_texture->setOpacity(100);
	addChild(sp_texture);

}

void HelloWorld::AboutRenderTextureNode()
{
	Sprite* sp = Sprite::create("CloseNormal.png");
	sp->runAction(MoveBy::create(2.0f, Vec2(100, 200)));


	RenderTexture* rt = RenderTexture::create(visibleSize.width, visibleSize.height, Texture2D::PixelFormat::RGBA4444);
	rt->setPosition(visibleSize / 2);
	addChild(rt);

	rt->addChild(sp);
	rt->setClearColor(Color4F(0, 0, 0, 0));
	rt->setClearFlags(GL_COLOR_BUFFER_BIT);
	rt->setAutoDraw(true);
}
class A {
public:
	A() {}
	~A() { log("delete"); }
};

A* fun()
{
	A* a = new A();
	log("in:a:%p", a);
	return a;
}

char* fun2()
{
	char b[3] = { 'a', 'b' };
	log("in:b:%p", b);
	log("in:b[0]:%c", b[0]);
	return b;
}

void HelloWorld::AboutWildPointer()
{
	A* a = fun();
	log("out:a%p", a);
	char* b = fun2();
	log("out:b:%p", b);
	log("out:b[0]:%c", b[0]);

	delete a;
	a = nullptr;
}

void HelloWorld::AboutAutoPolygon()
{
	Sprite* sp = Sprite::create("4000.png");
	sp->setPosition(visibleSize / 3);
	addChild(sp);

	auto pinfo = AutoPolygon::generatePolygon("4000.png");
	Sprite* ssp = Sprite::create(pinfo);
	ssp->setPosition(visibleSize / 2);
	addChild(ssp);

	//sp->debugDraw(true);
	//ssp->debugDraw(true);
}

void HelloWorld::AboutFastTileMap()
{
	#include "2d\CCFastTMXLayer.h"
	#include "2d\CCFastTMXTiledMap.h"
	auto map = cocos2d::experimental::TMXTiledMap::create("mission1-1.tmx");
	addChild(map);

	//auto map2 = TMXTiledMap::create("mission1-1.tmx");
	//addChild(map2);
}

void HelloWorld::AboutTextField()
{
	auto pTextField = TextFieldTTF::textFieldWithPlaceHolder("<click here!>", "Thonburi.ttf", 30);
	pTextField->setPosition(visibleSize / 2);
	addChild(pTextField);

	_trackNode = pTextField;
}

void HelloWorld::AboutProfilerDisplay()
{
	#undef CC_PROFILER_DISPLAY_TIMERS
	#define CC_PROFILER_DISPLAY_TIMERS() Profiler::getInstance()->displayTimers()
	#undef CC_PROFILER_PURGE_ALL
	#define CC_PROFILER_PURGE_ALL() Profiler::getInstance()->releaseAllTimers()

	#undef CC_PROFILER_START
	#define CC_PROFILER_START(__name__) ProfilingBeginTimingBlock(__name__)
	#undef CC_PROFILER_STOP
	#define CC_PROFILER_STOP(__name__) ProfilingEndTimingBlock(__name__)

	//CC_PROFILER_PURGE_ALL();
	CC_PROFILER_START("try");
	for (int i = 0; i < 4000; i++)
	{
		Node* node = Node::create();
	}
	CC_PROFILER_STOP("try");
	
	this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create([]() { CC_PROFILER_DISPLAY_TIMERS(); }), nullptr));
}

void HelloWorld::AboutClippingNodeAgain()
{
	auto clipNode = ClippingNode::create();
	clipNode->setPosition(visibleSize / 2);
	addChild(clipNode);
	clipNode->setAlphaThreshold(0.05);

	auto stencil = Sprite::create("btn_begin.png");
	clipNode->setStencil(stencil);

	auto sprite = Sprite::create("shadow.png");
	clipNode->addChild(sprite);
	sprite->runAction(RepeatForever::create(Sequence::create(MoveBy::create(3.0f, Vec2(200, 0)), MoveBy::create(3.0f, Vec2(-200, 0)), nullptr)));
}

void HelloWorld::AboutParticles()
{
}

KeyboardNotificationLayer::KeyboardNotificationLayer()
:_trackNode(nullptr)
{
	//register Touch Event
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(KeyboardNotificationLayer::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(KeyboardNotificationLayer::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void KeyboardNotificationLayer::keyboardWillShow(cocos2d::IMEKeyboardNotificationInfo & info)
{
}

bool KeyboardNotificationLayer::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event)
{
	log("began");
	_beginPos = touch->getLocation();

	return true;
}

void KeyboardNotificationLayer::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * event)
{
	log("touchEnd");
	if (!_trackNode)
		return;

	auto endPos = touch->getLocation();

	float delta = 5.f;
	if (std::abs(endPos.x - _beginPos.x) > delta ||
		std::abs(endPos.y - _beginPos.y) > delta)
	{
		//not click
		_beginPos.x = _beginPos.y = -1;
		return;
	}

	Rect rect;
	auto point = _trackNode->convertTouchToNodeSpace(touch);

	rect.size = _trackNode->getContentSize();
	this->onClickTrackNode(rect.containsPoint(point));

}
