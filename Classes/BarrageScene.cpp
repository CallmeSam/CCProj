#include "BarrageScene.h"
#include "ui\UIButton.h"
#include <array>
#include "OBBScene.h"

USING_NS_CC;
#define ENEMY_VELOCITY 2
#define ENEMY_ANGULAR 4

class SS
{
public :
};

typedef void (SS::*SOW)();

class SSW : public SS
{
public :
	void go(SS a,  SOW s)
	{
		(a.*s)();
	}
};

bool BarrageScene::init()
{
	if (!Scene::init())
		return false;
	
	initWithPhysics();
	_physicsWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_SHAPE);
	_physicsWorld->setGravity(Vec2::ZERO);

	/**/
	auto node = Node::create();
	node->setPosition(300, 600);
	addChild(node);
	
	auto sp = Sprite::create("tree2.png");
	sp->setAnchorPoint(Vec2(0.5f, 0.f));
	//auto physics = PhysicsBody::createBox(sp->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT, Vec2(0, sp->getContentSize().height / 2));
	//node->addComponent(physics);
	node->addChild(sp);
	//sp->setPosition(300, 200);


	


	return true;

	_enemyPool.reserve(100);

	_bullets = Node::create();
	addChild(_bullets);

	_enemies = Node::create();
	addChild(_enemies);

	createPlayer();

	auto btn = ui::Button::create("btn_begin.png");
	//addChild(btn);
	btn->setPosition(Vec2(400, 400));
	btn->addTouchEventListener([this](Ref*, ui::Widget::TouchEventType type) 
			{
				if (type == ui::Widget::TouchEventType::ENDED)
				{
					this->createBarrage();
				}
			}
	);

	srand(time(nullptr));

	scheduleUpdate();
	
	schedule([this](float dt) 
		{
			auto size = _enemies->getChildrenCount();	
			if (size < 50)
			{
				//auto actionM = Director::getInstance()->getActionManager();
				for (auto i = 0; i < 10; i++)
				{
					if (_enemyPool.empty())
						return;

					auto enemy = _enemyPool.back();
					_enemies->addChild(enemy);
					_enemyPool.popBack();
					auto body = PhysicsBody::createBox(enemy->getContentSize() * enemy->getScale());
					body->setCategoryBitmask(1 << 1);
					body->setCollisionBitmask(0);
					body->setContactTestBitmask(1);
					enemy->addComponent(body);
					//actionM->resumeTarget(enemy);
				}
			}
		}
	, 2.0f,  "generate Enemy");
	
	schedule([this](float dt)
	{
		this->createBarrage();
	}
	,  0.8f, "barrage");
	
	auto listener = EventListenerPhysicsContact::create();
	listener->onContactBegin = [](cocos2d::PhysicsContact& contact)->bool
		{
			auto spA = contact.getShapeA()->getBody()->getNode();
			auto spB = contact.getShapeB()->getBody()->getNode();
			if (!spA || !spB)
				return false;
			auto nameA = spA->getName();
			auto nameB = spB->getName();
			if ((nameA == "enemy" &&  nameB == "bullet") || (nameB == "enemy" &&  nameA == "bullet"))
			{
				spA->removeFromParent();
				spB->removeFromParent();

				return false;
			}

			return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto list = EventListenerTouchOneByOne::create();
	list->onTouchBegan = [](Touch*, Event*) {return true; };
	list->onTouchMoved = [this](Touch* ptouch, Event*) {
		auto delta = ptouch->getDelta();
		_player->setPosition(_player->getPosition() + delta);
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(list, this);

	return true;
}

void BarrageScene::createBarrage()
{
	auto pos = _player->getPosition();
	auto angular = _player->getRotation();
	for(auto i = 1; i > -2; i--)
		for (auto j = 1; j > -2; j--)
		{
			if (i == 0 && j == 0)
				continue;

			if (i != 0 || j != 1)
				continue;

			auto bullet = Sprite::create("zidan.png");
			auto body = PhysicsBody::createBox(bullet->getContentSize());
			body->setCategoryBitmask(1);
			body->setCollisionBitmask(0);
			body->setContactTestBitmask(1 << 1);
			bullet->addComponent(body);
			bullet->setName("bullet");
			_bullets->addChild(bullet);

			if (i == -1)
			{
				bullet->setRotation(-45 * (2 - j) + angular);
			}
			else if (i == 0)
			{
				if (j == 1)
					bullet->setRotation(angular);
				else if (j == -1)
					bullet->setRotation(angular + 180);
			}
			else
			{
				bullet->setRotation(45 * (2 - j) + angular);
			}

			//log("bullet rotation : %.2f", bullet->getRotation());
			auto radius = CC_DEGREES_TO_RADIANS(bullet->getRotation());
			bullet->setPosition(pos.x + sinf(radius) * 60, pos.y + cosf(radius) * 60);
			//log("bullet position : %.2f--%.2f", bullet->getPositionX(), bullet->getPositionY());

			//移动方向
			bullet->runAction(
				Sequence::create(
					MoveBy::create(2.0f, Vec2(1300 * sinf(radius), 1300 * cosf(radius))),
					RemoveSelf::create(),
					nullptr
				));
			
		}
}

void BarrageScene::createPlayer()
{
	_player = Sprite::create("tree2.png");
	addChild(_player);
	_player->setPosition(360, 640);
	_player->runAction(
		RepeatForever::create(
			RotateBy::create(3.0f, 360)
		)
	);
}

cocos2d::Sprite* BarrageScene::createEnemy()
{
	auto enemy = Sprite::create("green.png");
	enemy->setScale(0.4f);
	enemy->setName("enemy");
	auto dir = random(1, 4);
	auto size = Director::getInstance()->getVisibleSize();
	switch (dir)
	{
	case 1:
		enemy->setPosition(0, rand_0_1() * size.height);
		//enemy->setRotation(random(-45, 45));
		break;
	case 2:
		enemy->setPosition(rand_0_1() * size.width, 0);
		//enemy->setRotation(random(-135, -45));
		break;
	case 3:
		enemy->setPosition(size.width, rand_0_1() * size.height);
		//enemy->setRotation(random(135, 225));
		break;
	case 4:
		enemy->setPosition(rand_0_1() * size.width,  size.height);
		//enemy->setRotation(random(-225, -135));
		break;
	default:
		break;
	}
	//_enemies->addChild(enemy);
	auto act = Sequence::create(
		MoveTo::create(4.0f, Vec2(480, 320)),
		RemoveSelf::create(),
		nullptr
	);
	//Director::getInstance()->getActionManager()->addAction(act, enemy, true);
	return enemy;
}

void BarrageScene::addEnemyToPool()
{
	if (_enemyPool.size() < 100)
	{
		_enemyPool.pushBack(this->createEnemy());
	}
}

void BarrageScene::moveTowardsPlayer(cocos2d::Node* node)
{
	auto enemyPos = node->getPosition();
	auto playerPos = _player->getPosition();
	auto destVec = (playerPos - enemyPos).getNormalized();
	//atan2的范围是(-180, 180]
	auto needAngular = CC_RADIANS_TO_DEGREES(atan2f(destVec.y , destVec.x));
	auto curAngular = - node->getRotation();
	curAngular = curAngular >= 360 ? curAngular - 360 : curAngular <= -360 ? curAngular + 360 : curAngular;

	auto tempAngular = needAngular - curAngular;
	if (tempAngular > 180 || tempAngular < -180)
	{
		if (curAngular >= 0)
			curAngular -= 360;
		else
			curAngular += 360;

		tempAngular = needAngular - curAngular;
	}
	
	if (tempAngular > 0)
	{
		tempAngular = tempAngular > ENEMY_ANGULAR ? ENEMY_ANGULAR : tempAngular;
		node->setRotation(node->getRotation() - tempAngular);
	}
	else if(tempAngular < 0)
	{
		tempAngular = abs(tempAngular) > ENEMY_ANGULAR ? -ENEMY_ANGULAR : tempAngular;
		node->setRotation(node->getRotation() - tempAngular);
	}
	auto toward = CC_DEGREES_TO_RADIANS(-node->getRotation());
	auto deltaVec = Vec2(cosf(toward) * ENEMY_VELOCITY, sinf(toward) * ENEMY_VELOCITY);
	node->setPosition(node->getPosition() + deltaVec);
}

void BarrageScene::spacePartition(std::array<std::array<std::vector<cocos2d::Node*>, ROW>, COL>& map)
{
	for (const auto &child : _enemies->getChildren())
	{
		auto rect = child->getBoundingBox();
		Vec2 point[4];
		this->getVerts(rect, point);
		//获得最小和最大点，在这个范围中遍历
		auto min = getPos(point[0]);
		auto max = getPos(point[3]);
		//区域外的不做碰撞处理
		for (auto i = min.x; i <= max.x; i++)
		{
			if (i < 0 || i > COL - 1)
				continue;
			for (auto j = min.y; j <= max.y; j++)
			{
				if (j < 0 || j > ROW - 1)
					continue;

				map[i][j].push_back(child);
			}
		}
	}
}

void BarrageScene::collideWithObjects(std::array<std::array<std::vector<cocos2d::Node*>, ROW>, COL>& map, std::vector<cocos2d::Node*>& deleteList)
{
	auto children = _bullets->getChildren();
	auto size = children.size();
	for (int i = 0; i < size; i++)
	{
		auto isCollide = false;
		auto boundBox = children.at(i)->getBoundingBox();

		Vec2 verts[4];
		this->getVerts(boundBox, verts);
		//获得最小和最大点，在这个范围中遍历
		auto min = getPos(verts[0]);
		auto max = getPos(verts[3]);
		//区域外的不做碰撞处理
		for (int j = min.x; j <= max.x; j++)
		{
			if (isCollide)
				break;

			if (j < 0 || j >	COL - 1)
				continue;

			for (int k = min.y; k <= max.y; k++)
			{
				if (k < 0 || k > ROW - 1)
					continue;

				for(auto& child : map[j][k])
				{
					if (!child || child->getName() == "delete")
						return;

					OBB_2 obbA(children.at(i)->getPosition(), -children.at(i)->getRotation(), children.at(i)->getContentSize());
					OBB_2 obbB(child->getPosition(), -child->getRotation(), child->getContentSize());
					if (obbA.isCollideWithOBB(obbB))
					{
						children.at(i)->removeFromParent();
						child->setName("delete");
						deleteList.push_back(child);
						isCollide = true;
						break;
					} 
				}
				if (isCollide)
					break;
			}

		}
	}
}

cocos2d::Vec2 BarrageScene::getPos(cocos2d::Vec2 point)
{
	auto col = floor(point.x / 60);
	auto row = floor(point.y / 90);

	return Vec2(col, row);
}

void BarrageScene::getVerts(const cocos2d::Rect & rect, cocos2d::Vec2 * points)
{
	points[0] = rect.origin;
	points[1] = rect.origin + Vec2(rect.size.width, 0);
	points[2] = rect.origin + Vec2(0, rect.size.height);
	points[3] = rect.origin + rect.size;
}

void BarrageScene::update(float dt)
{
	addEnemyToPool();
	for (auto child : _enemies->getChildren())
		moveTowardsPlayer(child);

	return;

	std::array<std::array<std::vector<cocos2d::Node*>, ROW>, COL> map;
	spacePartition(map);
	std::vector<cocos2d::Node*> list;
	collideWithObjects(map, list);
	for (auto& child : list)
	{
		child->removeFromParent();
		child = nullptr;
	}
}


