#include "BuffBase.h"
#include "cocos2d.h"

const BuffTime BuffTime::OneTick{ 0, 0, 0 };

BuffBase::BuffBase()
{
	_id = 0;
	_isBegin = false;
	_isDelay = false;
	_aborted = false;
	_isSleep = true;
	_priority = 0;
	_time = BuffTime::OneTick;
	_elapsed = 0.f;
	_owner = nullptr;
	_sower = nullptr;
}

void BuffBase::onBuffOccur()
{
	if (_isSleep)
		return;
}

void BuffBase::onBuffEnd()
{
	if (_isSleep)
		return;
}

void BuffBase::onBuffTick()
{
	if (_isSleep)
		return;
}

void BuffBase::update(float dt)
{
	if (_aborted)
		return;

	if (!_isBegin)
	{
		_isBegin = true;
		if (!_isDelay)
		{
			onBuffOccur();
		}
		else
		{
			_elapsed += dt;
			if (_elapsed >= _time.delayTime)
			{
				_isDelay = false;
				_elapsed = 0;
				onBuffOccur();
			}
		}
		return;
	}

	_elapsed += dt;
	_time.totalTime -= dt;
	_aborted = _time.totalTime > 0 ? false : true;
	//cocos2d::log("id:%d, time : %.3f", _id, _time.totalTime);

	if (_time.interval > 0)
	{
		while (_elapsed >= _time.interval && !_aborted)
		{
			_elapsed -= _time.interval;
			onBuffTick();
		}
	}

	if (_aborted)
	{
		onBuffEnd();
	}
}

void BuffBase::refresh(int level)
{
	_isBegin = false;
	_aborted = false;
	_elapsed = 0.f;
}

void BuffBase::addLV()
{

}

void BuffBase::buffAwake()
{
}

bool BuffBase::compareToOther(BuffBase * other)
{
	return false;
}

void BuffBase::destory()
{
	delete this;
}

void BuffBase::setBuffSleep(bool isSleep)
{
	if (_isSleep = isSleep)
		return;
	_isSleep = isSleep;
	if (!_isSleep && _isBegin)
		buffAwake();
}
