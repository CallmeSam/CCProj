#include "GameScene.h"
#include "tools\Parser.h"
#include "Config\GameConfig.h"
#include "SpecialSkills.h"
#include "SkillFactory.h"
#include "BarrageDemo\Enemies.h"

USING_NS_CC;

bool GameScene::init()
{
	if (!Scene::initWithPhysics())
		return false;

	Parser::ParserJsonToValueVector("Barrage/data/skillInfo.json", SKILL_INFO);
	Parser::ParserJsonToValueVector("Barrage/data/enemiesInfo.json", ENEMIES_INFO);
	Parser::ParserJsonToValueVector("Barrage/data/buffInfo.json", BUFF_INFO);

	//初始化物理世界
	{
		//_physicsWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_SHAPE);
		_physicsWorld->setGravity(Vec2::ZERO);
	}

	_vecE.reserve(50);

	_bullets = Node::create();
	addChild(_bullets);

	_enemies = Node::create();
	addChild(_enemies);

	createPlayer();

	schedule([this](float dt)
	{
		this->createBarrage(DIRECTION::UP);
		//this->createBarrage(DIRECTION::DOWN);
		//this->createBarrage(DIRECTION::RIGHT);
		//this->createBarrage(DIRECTION::LEFT);
	}
	, 0.8f, "barrage");


	schedule([this](float dt) 
	{
		if (_vecE.empty() || _enemies->getChildrenCount() > 150)
			return;

		auto size = _vecE.size() > 15 ? 15 : _vecE.size();
		for (auto i = 0; i < size; i++)
		{
			_enemies->addChild(_vecE.back());
			_vecE.popBack();
		}
	}
	, 2.5f, "enemy");

	scheduleUpdate();

	auto listener = EventListenerPhysicsContact::create();
	listener->onContactBegin = [](cocos2d::PhysicsContact& contact)->bool
	{
		auto spA = contact.getShapeA()->getBody()->getNode();
		auto spB = contact.getShapeB()->getBody()->getNode();
		if (!spA || !spB)
			return false;
		
		auto objectA = static_cast<ObjectBase*>(spA);
		auto objectB = static_cast<ObjectBase*>(spB);

		if (objectA->getIsDead() || objectB->getIsDead())
			return false;

		auto boolA = objectA->collideWithObject(objectB);
		auto boolB = objectB->collideWithObject(objectA);

		return boolA && boolB;
	};

	listener->onContactSeparate = [](cocos2d::PhysicsContact& contact)
	{
		auto spA = contact.getShapeA()->getBody()->getNode();
		auto spB = contact.getShapeB()->getBody()->getNode();
		if (!spA || !spB)
			return ;

		auto objectA = static_cast<ObjectBase*>(spA);
		auto objectB = static_cast<ObjectBase*>(spB);

		objectA->seperateWithObject(objectB);
		objectB->seperateWithObject(objectA);
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void GameScene::createPlayer()
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

void GameScene::createEnemies()
{
	if (_vecE.size() >= 50)
		return;

	static int tag = 1;
	auto dir = random(1, 4);
	auto enemy = Enemies::createWithId(1, 1);

	if (dir == 1)
	{
		enemy->setRotation(90);
		enemy->setPosition(-30, 100 + 1000 * rand_0_1());
	}
	else if (dir == 2)
	{
		enemy->setRotation(180);
		enemy->setPosition(100 + 400 * rand_0_1(), 1400);
	}
	else if (dir == 3)
	{
		enemy->setRotation(-90);
		enemy->setPosition(800, 100 + 1000 * rand_0_1());
	}
	else if (dir == 4)
	{
		enemy->setRotation(0);
		enemy->setPosition(100 + 400 * rand_0_1(), -50);
	}
	
	enemy->addBuff(6, 1);
	enemy->setTag(tag++);
	_vecE.pushBack(enemy);
}

void GameScene::createBarrage(DIRECTION dir)
{
	float rotation;
	constexpr int dis = 50;
	int id = 1;
	switch (dir)
	{
	case DIRECTION::UP:
		rotation = 0;
		id = 7;
		break;
	case DIRECTION::DOWN:
		rotation = 180;
		//id = 2;
		break;
	case DIRECTION::LEFT:
		rotation = -90;
		//id = 4;
		break;
	case DIRECTION::RIGHT:
		rotation = 90;
		//id = 6;
		break;
	default:
		break;
	}

	auto skill = SkillsFactory::createSkillWithId(id);
	
	auto totalRotate = _player->getRotation() + rotation;
	skill->setRotation(totalRotate);
	float radius = CC_DEGREES_TO_RADIANS(-totalRotate + 90);
	Vec2 offset = Vec2(cosf(radius), sinf(radius)) * dis;
	skill->setPosition(_player->getPosition() + offset);
	_bullets->addChild(skill);
}

void GameScene::update(float dt)
{
	createEnemies();

	auto vecBullet = _bullets->getChildren();
	for (auto& child : vecBullet)
	{
		auto bullet = static_cast<Skills*>(child);
		if (bullet->getIsDead())
		{
			bullet->destory();
			bullet->removeFromParent();
			continue;
		}

		bullet->updateObj(dt);
	}

	auto vecEnemies = _enemies->getChildren();
	for (auto& child : vecEnemies)
	{
		auto enemy = static_cast<ObjectMove*>(child);
		if (enemy->getIsDead())
		{
			enemy->destory();
			enemy->removeFromParent();
			continue;
		}

		enemy->updateObj(dt);
	}

}
