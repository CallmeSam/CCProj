#include "Enemies.h"
#include "Config\GameConfig.h"

USING_NS_CC;
Enemies * Enemies::createWithId(int enemyId, int level)
{
	auto skill = new(std::nothrow)Enemies();
	if (skill && skill->init(enemyId, level))
	{
		skill->autorelease();
		return skill;
	}
	CC_SAFE_DELETE(skill);
	return nullptr;
}

bool Enemies::init(int enemyId, int level)
{
	if (!ObjectMove::init(enemyId, level))
		return false;

	_type = ObjectType::ENEMY;
	//初始化数据
	auto& info = ENEMIES_INFO[enemyId - 1].asValueMap();
	auto upgradeInfo = info["upgrade"].asValueMap();
	_speed = info["speed"].asFloat();
	_damage = info["damage"].asFloat();
	_life = info["life"].asFloat();
	auto scale = info["scale"].asFloat();
	_sp = Sprite::create(info["pic"].asString());
	_sp->setScale(1.0f + scale);
	addChild(_sp);
	
	//physicsBody
	auto physicsBody = PhysicsBody::createBox(getSpSize());
	physicsBody->setCategoryBitmask(ENEMY_CATEGORY_MASK);
	physicsBody->setCollisionBitmask(0);
	physicsBody->setContactTestBitmask(ENEMY_CONTACT_MASK);
	this->addComponent(physicsBody);

	//加载buff

	return true;
}


cocos2d::ValueMap& Enemies::getInfo()
{
	return ENEMIES_INFO[_id - 1].asValueMap();
}

void Enemies::getHurt(float damage)
{
	_life -= damage;
	
	log("mylife %.2f", _life);

	if (_life <= 0.f)
	{
		_isDead = true;
	}
}

bool Enemies::collideWithObject(ObjectBase * node)
{
	if (!ObjectMove::collideWithObject(node))
		return false;
	
	if (node->getObjType() == ObjectType::BULLET)
	{
		auto bullet = static_cast<ObjectMove*>(node);
		getHurt(bullet->getDamage());
	}
	else if (node->getObjType() == ObjectType::PLAYER)
	{
		_isDead = true;
	}

	return !_isDead;
}

