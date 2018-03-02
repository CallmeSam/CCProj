#include "BuffHurt.h"
#include "BarrageDemo\Config\GameConfig.h"
#include "BarrageDemo\Enemies.h"

BuffHurt::BuffHurt(int id, int level, ObjectBase * owner)
{
	_id = id;
	_owner = owner;
	refresh(level);
}

void BuffHurt::onBuffOccur()
{
	if (_isSleep)
		return;

	auto enemy = static_cast<Enemies*>(_owner);
	enemy->getHurt(_life);
}

void BuffHurt::onBuffTick()
{
	onBuffOccur();
}

bool BuffHurt::compareToOther(BuffBase * other)
{
	auto oth = static_cast<BuffHurt*>(other);
	return _life < oth->getDamage();
}

void BuffHurt::refresh(int level)
{
	BuffBase::refresh(level);

	auto info = BUFF_INFO[_id - 1].asValueMap();
	auto upgradeInfo = info["upgrade"].asValueMap();
	_life = info["life"].asFloat() + upgradeInfo["life"].asFloat() * (level - 1);
	float delayTime = info["delayTime"].asFloat() + upgradeInfo["delayTime"].asFloat() * (level - 1);
	float totalTime = info["totalTime"].asFloat() + upgradeInfo["totalTime"].asFloat() * (level - 1);
	float interval = info["interval"].asFloat() + upgradeInfo["interval"].asFloat() * (level - 1);
	_time = BuffTime{ delayTime, totalTime, interval };
	_isDelay = _time.delayTime > 0 ? true : false;
}
