#include "PhysicsScene.h"
USING_NS_CC;

bool PhysicsScene::init()
{
	if(!Scene::init())
		return false;
	visibleSize = Director::getInstance()->getVisibleSize();
	_angle = .0f;
	//初始化物理场景
	initWithPhysics();

	//AboutRayCast();
	//AboutCollisionBitmask();

	return true;
}



void PhysicsScene::update(float dt)
{

	//sp->setPositionY(sp->getPositionY() + 10);
	
	log("%f", sp->getPositionY());
	for (int i = 0; i < 3; ++i)
	{
		this->getPhysicsWorld()->step(1 / 180.0f);
	}

	float L = 150.0f;
	Vec2 point1 = Vec2(visibleSize.width/2, visibleSize.height/3);
	Vec2 d(L * cosf(_angle), L * sinf(_angle));
	Vec2 point2 = point1 + d;

	removeChild(_node);
	_node = DrawNode::create();
	Vec2 point3 = point2;
	auto func = CC_CALLBACK_3(PhysicsScene::callbackForRayCast, this);
	float friction = 0.97f;
	PhysicsRayCastCallbackFunc func2 = [&point3, &friction](PhysicsWorld& world, const PhysicsRayCastInfo& info, void* data)->bool
	{
		if (friction > info.fraction)
		{
			point3 = info.contact;
			friction = info.fraction;
		}
		//扫描到一个就不再继续了
		return false;
	};
	getPhysicsWorld()->rayCast(func2, point1, point2, &point3);
	_node->drawSegment(point1, point3, 1, Color4F::BLUE);

	if (point2 != point3)
	{
		_node->drawDot(point3, 2, Color4F(1.0f, 1.0f, 1.0f, 1.0f));
	}
	addChild(_node);
	_angle -= 0.25f * (float)M_PI / 180.0f;

	//Vec2 pos = _sphere->getPosition();
	//float rotation = _sphere->getPhysicsBody()->getRotation();
	//removeChild(_sphere);

	//log("rotation:%f", rotation);
	//_sphere->clear();
	//_sphere->drawCircle(Vec2(50 , 200 ), 20, rotation , 20, true, Color4F::GRAY);
	//_sphere->setRotation(_sphere->getPhysicsBody()->getRotation());
	//log("%f", sp->getPositionY());
}

void PhysicsScene::onEnter()
{
	Scene::onEnter();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	//getPhysicsWorld()->setGravity(Vec2(0, 0));
	//默认1.0，数越小，算的越精密、越大、越快但是越渣，必须setAutoStep(true)的情况才可以
	//getPhysicsWorld()->setUpdateRate(1.0);
	getPhysicsWorld()->setAutoStep(false);
	sp = Sprite::create("CloseSelected.png");
	sp->setPosition(100, 30);
	//PhysicsMaterial mass bounce(restitution) friction 质量、弹性、摩擦力
	auto spBody = PhysicsBody::createBox(sp->getContentSize(), PhysicsMaterial(0.1f, 0.5f, 0.5f));
	
	spBody->setVelocity(Vect(100, 0));
	//spBody->applyForce(Vect(-20, 0));
	log("%f", spBody->getMass());
	log("%f -- %f", spBody->getLinearDamping(), spBody->getAngularDamping());
	sp->setPhysicsBody(spBody);
	addChild(sp);
	//sp->setVisible(true);

	log("%f--%f", sp->getPositionX(), sp->getPositionY());

	Node* node = Node::create();
	node->setPosition(visibleSize / 2);
	node->setPhysicsBody(PhysicsBody::createEdgeBox(visibleSize));
	addChild(node);

	auto rope = Node::create();
	Vec2 points[] =
	{
		Vec2(0, 0),
		Vec2(visibleSize.width / 2, 0),
		Vec2(visibleSize.width, 0)
	};
	auto ropeBody = PhysicsBody::createEdgeChain(points, 3);
	rope->setPhysicsBody(ropeBody);
	log("%f", rope->getPhysicsBody()->getLinearDamping());
	rope->setPositionY(rope->getPositionY() + 10);
	addChild(rope);
	
	getPhysicsWorld()->step(0);
	
	scheduleUpdate();
}

void PhysicsScene::AboutCollisionBitmask()
{
	_sphere = DrawNode::create();
	_sphere->drawCircle(Vec2(200, 300), 20, 30.0f/180.0f * M_PI, 20, true, Color4F::GRAY);
	_sphere->setPhysicsBody(PhysicsBody::createCircle(20, PhysicsMaterial(0.3, 0.5, .0f), Vec2(200, 300)));
	auto body1 = _sphere->getPhysicsBody();
	body1->setGroup(-1);
	//_sphere->getPhysicsBody()->setCategoryBitmask(0x1);
	//_sphere->getPhysicsBody()->setCollisionBitmask(0x2);
	body1->setContactTestBitmask(1);
	_sphere->getPhysicsBody()->applyTorque(30);

	Sprite*sp = Sprite::create("CloseNormal.png");
	sp->setPhysicsBody(PhysicsBody::createCircle(10));
	auto body2 = sp->getPhysicsBody();
	//sp->getPhysicsBody()->setCategoryBitmask(0x2);
	//sp->getPhysicsBody()->setCollisionBitmask(0x1);
	body2->setGroup(1);
	body2->setContactTestBitmask(1);
	sp->setPosition(Vec2(200, 350));
	addChild(sp);
	addChild(_sphere);

	PhysicsJointPin* joint = PhysicsJointPin::construct(body1, body2, Vec2(80, 300));
	//getPhysicsWorld()->addJoint(joint);

	auto listener = EventListenerPhysicsContact::create();
	listener->onContactBegin = [](PhysicsContact& contact)->bool {
		Node* node1 = contact.getShapeA()->getBody()->getNode();
		Node* node2 = contact.getShapeA()->getBody()->getNode();
		log("HaHa!");
		log("count:%d", contact.getContactData()->count);
		log("count:%f", contact.getContactData()->points[0].x);
		log("normal:x:%f  y:%f", contact.getContactData()->normal.x, contact.getContactData()->normal.y);
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void PhysicsScene::AboutRayCast()
{
	_node = DrawNode::create();
	_node->drawSegment(Vec2(visibleSize.width / 2, 100), Vec2(visibleSize.width / 2, 20), 1, Color4F::WHITE);
	_node->setPhysicsBody(PhysicsBody::createEdgeSegment(Vec2(visibleSize.width / 2, 100), Vec2(visibleSize.width / 2, 20)));
	//getPhysicsWorld()->step(0);
	addChild(_node);
}

bool PhysicsScene::callbackForRayCast(cocos2d::PhysicsWorld & world, const cocos2d::PhysicsRayCastInfo & info, void * data)
{
	*((Vec2*)data) = info.contact;
	return false;
}
