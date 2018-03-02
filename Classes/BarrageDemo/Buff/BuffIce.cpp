#include "BuffIce.h"
#include "BarrageDemo\ObjectBase.h"
#include "BarrageDemo\Config\GameConfig.h"
#include "BarrageDemo\ObjectMove.h"

BuffIce::BuffIce(int id, int level, ObjectBase* owner)
{
	_id = id;
	_owner = owner;
	refresh(level);
}

void BuffIce::onBuffOccur()
{
	if (_isSleep)
		return;

	auto obj = static_cast<ObjectMove*>(_owner);
	//×ÜËÙ¶È
	auto speed = obj->getInfo()["speed"].asFloat();
	obj->setSpeed(speed * (1 - _ratio));
}

void BuffIce::onBuffEnd()
{
	if (_isSleep)
		return;

	auto obj = static_cast<ObjectMove*>(_owner);
	auto speed = obj->getInfo()["speed"].asFloat();
	obj->setSpeed(speed);
}

void BuffIce::buffAwake()
{
	onBuffOccur();
}

void BuffIce::refresh(int level)
{
	BuffBase::refresh(level);

	auto info = BUFF_INFO[_id - 1].asValueMap();
	auto upgradeInfo = info["upgrade"].asValueMap();
	_ratio = info["ratio"].asFloat() + upgradeInfo["ratio"].asFloat() * (level - 1);
	float delayTime = info["delayTime"].asFloat() + upgradeInfo["delayTime"].asFloat() * (level - 1);
	float totalTime = info["totalTime"].asFloat() + upgradeInfo["totalTime"].asFloat() * (level - 1);
	float interval = info["interval"].asFloat() + upgradeInfo["interval"].asFloat() * (level - 1);
	_time = BuffTime{ delayTime, totalTime, interval };
	_isDelay = _time.delayTime > 0 ? true : false;
}

bool BuffIce::compareToOther(BuffBase * other)
{
	auto oth = static_cast<BuffIce*>(other);
	return _ratio < oth->getRatio();
}
