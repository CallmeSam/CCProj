#include "ObjectMove.h"
#include "BarrageDemo\Config\GameConfig.h"

USING_NS_CC;

bool ObjectMove::init(int id, int level)
{
	if (!Node::init())
		return false;

	_id = id;
	_level = level;
	_isDead = false;

	_speed = 0.f;
	_damage = 0.f;

	_buffsIn.clear();
	_buffsTo.clear();

	_rotate = PER_ROTATE;

	return true;
}

void ObjectMove::move(float dt)
{
	auto degree = CC_DEGREES_TO_RADIANS(-this->getRotation() + 90);
	_dst.realValue = Vec2(_speed * cosf(degree) * dt, _speed * sinf(degree) * dt);
}

bool ObjectMove::updateObj(float dt)
{
	//Íâ²¿ÊÍ·Å
	if (_isDead)
		return false;

	_dst.realValue = Vec2::ZERO;
	_dst.extraValue = Vec2::ZERO;

	updateBuff(dt);
	move(dt);

	this->setPosition(this->getPosition() + _dst.realValue + _dst.extraValue);

	return true;
}


cocos2d::ValueMap& ObjectMove::getInfo()
{
	return EMPTY_MAP;
}

