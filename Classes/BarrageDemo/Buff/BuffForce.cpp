#include "BuffForce.h"
#include "BarrageDemo\Config\GameConfig.h"
#include "BarrageDemo\ObjectMove.h"

BuffForce::BuffForce(int id, int level, ObjectBase * owner)
{
	_id = id;
	_owner = owner;

	refresh(level);
}

BuffForce::BuffForce(int id, int level, ObjectBase * owner, cocos2d::Vec2 dst)
	:BuffForce::BuffForce(id, level, owner)
{
	_isUseDir = false;
	_dst = dst;
}

BuffForce::BuffForce(int id, int level, ObjectBase * owner, float dir)
	: BuffForce::BuffForce(id, level, owner)
{
	_isUseDir = true;
	_dir = CC_DEGREES_TO_RADIANS(dir);
}

void BuffForce::onBuffOccur()
{
	if (_isSleep)
		return;

	auto obj = static_cast<ObjectMove*>(_owner);

	//如果是朝着一个方向拉动
	if (_isUseDir)
	{
		obj->changeExtraDst(_force * cocos2d::Vec2(cosf(_dir), sinf(_dir)));
		return;
	}
	
	auto s = _dst - _owner->getPosition();
	auto length = s.getLength();
	if (length <= _range)
	{
		auto ratio = (_range - length) / _range;
		if (length <= _force * (1 + ratio))
		{
			obj->changeExtraDst(s);
		}
		else
		{
			obj->changeExtraDst(s.getNormalized() * _force *(1 + ratio));
		}
	}
	else
	{
		obj->changeExtraDst(s.getNormalized() * _force);
	}
}

void BuffForce::onBuffTick()
{
	onBuffOccur();
}

bool BuffForce::compareToOther(BuffBase * other)
{
	auto oth = static_cast<BuffForce*>(other);
	return _force < oth->getForce();
}

void BuffForce::refresh(int level)
{
	BuffBase::refresh(level);

	auto info = BUFF_INFO[_id - 1].asValueMap();
	auto upgradeInfo = info["upgrade"].asValueMap();
	_range = info["range"].asFloat() + upgradeInfo["range"].asFloat() * (level - 1);
	_force = info["strength"].asFloat() + upgradeInfo["strength"].asFloat() * (level - 1);
	float delayTime = info["delayTime"].asFloat() + upgradeInfo["delayTime"].asFloat() * (level - 1);
	float totalTime = info["totalTime"].asFloat() + upgradeInfo["totalTime"].asFloat() * (level - 1);
	float interval = info["interval"].asFloat() + upgradeInfo["interval"].asFloat() * (level - 1);
	_time = BuffTime{ delayTime, totalTime, interval };
	_isDelay = _time.delayTime > 0 ? true : false;
}
