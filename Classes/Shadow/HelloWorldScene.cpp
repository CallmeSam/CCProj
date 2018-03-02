#include "HelloWorldScene.h"
#include "RemindShader.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

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
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

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
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

	m_pShader = RemindShader::create();
	m_pShader->setPosition(Vec2(100, 100));
	this->addChild(m_pShader);
    // add "HelloWorld" splash screen"
	m_pNode = Sprite::create("HelloWorld.png");

	auto camera = Camera::create();
	camera->setCameraFlag(CameraFlag::USER1);
	//m_pShader->addChild(camera);

	auto pMove1 = MoveBy::create(5, Vec2(300, 100));
	auto pMove2 = MoveBy::create(5, Vec2(-300, -100));
	auto pSequenceMove = Sequence::createWithTwoActions(pMove1, pMove2);
	auto pRepeatMove = RepeatForever::create(pSequenceMove);
	m_pShader->runAction(pRepeatMove->clone());
	//camera->runAction(pRepeatMove->clone());
    // add the sprite as a child to this layer
	m_pShader->addChild(m_pNode, 0);
	//m_pShader->setCameraMask(1 << 1);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](cocos2d::Touch* touch, cocos2d::Event* event) 
	{
		this->m_pShader->setPosition(touch->getLocation());
		return true;
	};

	listener->onTouchMoved = [this](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		this->m_pShader->setPosition(touch->getLocation());
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void HelloWorld::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	if (m_pShader)
	{
		m_pShader->push2Draw(m_pNode);
	}
}
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
