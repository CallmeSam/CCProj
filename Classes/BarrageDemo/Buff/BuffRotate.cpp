#include "BuffRotate.h"
#include "BarrageDemo\Config\GameConfig.h"
#include "BarrageDemo\ObjectMove.h"

BuffRotate::BuffRotate(int id, int level, ObjectBase * owner)
{
	_id = id;
	_owner = owner;
	refresh(level);
}

void BuffRotate::onBuffOccur()
{
	if (_isSleep)
		return;

	auto obj = static_cast<ObjectMove*>(_owner);
	obj->setRotate(_rotate);

}

void BuffRotate::onBuffEnd()
{
	if (_isSleep)
		return;

	auto obj = static_cast<ObjectMove*>(_owner);;
	obj->setRotate(PER_ROTATE);
}

void BuffRotate::buffAwake()
{
	onBuffOccur();
}

void BuffRotate::refresh(int level)
{
	BuffBase::refresh(level);

	auto info = BUFF_INFO[_id - 1].asValueMap();
	auto upgradeInfo = info["upgrade"].asValueMap();
	_rotate = info["rotate"].asFloat() + upgradeInfo["rotate"].asFloat() * (level - 1);
	float delayTime = info["delayTime"].asFloat() + upgradeInfo["delayTime"].asFloat() * (level - 1);
	float totalTime = info["totalTime"].asFloat() + upgradeInfo["totalTime"].asFloat() * (level - 1);
	float interval = info["interval"].asFloat() + upgradeInfo["interval"].asFloat() * (level - 1);
	_time = BuffTime{ delayTime, totalTime, interval };
	_isDelay = _time.delayTime > 0 ? true : false;
}

bool BuffRotate::compareToOther(BuffBase * other)
{
	auto oth = static_cast<BuffRotate*>(other);
	return _rotate < oth->getRotate();
}
