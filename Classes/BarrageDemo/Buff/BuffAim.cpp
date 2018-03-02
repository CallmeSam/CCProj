#include "BuffAim.h"
#include "BarrageDemo\Config\GameConfig.h"
#include "BarrageDemo\GameScene.h"
#include "BarrageDemo\ObjectMove.h"


BuffAim::BuffAim(int id, int level, ObjectBase * owner)
{
	_id = id;
	_owner = owner;
	
	refresh(level);
}

void BuffAim::towardToObject(cocos2d::Node * obj, int rotate)
{
	auto enemyPos = _owner->getPosition();
	auto objPos = obj->getPosition();
	auto destVec = (objPos - enemyPos).getNormalized();
	//atan2µÄ·¶Î§ÊÇ(-180, 180]
	auto needAngular = CC_RADIANS_TO_DEGREES(atan2f(destVec.y, destVec.x));
	auto curAngular = -_owner->getRotation() + 90;
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
		tempAngular = tempAngular > rotate ? rotate : tempAngular;
		_owner->setRotation(_owner->getRotation() - tempAngular);
		//cocos2d::log("angular : %.2f", -tempAngular);
	}
	else if (tempAngular < 0)
	{
		tempAngular = abs(tempAngular) > rotate ? -rotate : tempAngular;
		_owner->setRotation(_owner->getRotation() - tempAngular);
		//cocos2d::log("angular : %.2f", -tempAngular);
	}
}

void BuffAim::onBuffOccur()
{
	if (_isSleep)
		return;

	auto moveObj = static_cast<ObjectMove*>(_owner);
	auto rotate = moveObj->getRotate();
	if (rotate == 0)
		return;

	auto scene = static_cast<GameScene*>(cocos2d::Director::getInstance()->getRunningScene());
	cocos2d::Node* target = nullptr;
	cocos2d::Node* vec = nullptr;
	switch (_type)
	{
	case FIND_TYPE::NONE:
		target = nullptr;
		break;
	case FIND_TYPE::ENEMY:
		vec = scene->getEnemies();
		target = vec->getChildByTag(_targetTag);
		break;
	case FIND_TYPE::BULLET:
		vec = scene->getBullets();
		target = vec->getChildByTag(_targetTag);
		break;
	case FIND_TYPE::PLAYER:
		target = scene->getPlayer();
		break;
	default:
		break;
	}
	
	if (!target)
	{
		if (!vec)
			return;

		auto size = vec->getChildrenCount();
		switch (_way)
		{
		case FIND_WAY::NONE:
			break;
		case FIND_WAY::RANDOM:
			if (size > 0)
			{
				target = vec->getChildren().at(cocos2d::random(0, int(size - 1)));
			}
			break;
		case FIND_WAY::NEAREST:
			for (const auto& child : vec->getChildren())
			{
				if (target)
				{
					auto length = (child->getPosition() - _owner->getPosition()).getLength();
					if (length < (target->getPosition() - _owner->getPosition()).getLength())
					{
						target = child;
					}
				}
				else
				{
					target = child;
				}
			}
			break;
		default:
			break;
		}

		if (target)
		{
			_targetTag = target->getTag();
		}
		else
		{
			return;
		}
	}

	towardToObject(target, rotate);
}

void BuffAim::onBuffTick()
{
	onBuffOccur();
}

void BuffAim::refresh(int level)
{
	BuffBase::refresh(level);

	_targetTag = -2;

	auto info = BUFF_INFO[_id - 1].asValueMap();
	auto upgradeInfo = info["upgrade"].asValueMap();

	float delayTime = info["delayTime"].asFloat() + upgradeInfo["delayTime"].asFloat() * (level - 1);
	float totalTime = info["totalTime"].asFloat() + upgradeInfo["totalTime"].asFloat() * (level - 1);
	float interval = info["interval"].asFloat() + upgradeInfo["interval"].asFloat() * (level - 1);
	_time = BuffTime{ delayTime, totalTime, interval };
	_isDelay = _time.delayTime > 0 ? true : false;

	{
		auto type = info["type"].asString();
		_type = type == "enemy" ? FIND_TYPE::ENEMY : type == "player" ? FIND_TYPE::PLAYER : type == "bullet" ? FIND_TYPE::BULLET : FIND_TYPE::NONE;
		auto way = info["way"].asString();
		_way = way == "random" ? FIND_WAY::RANDOM : way == "nearest" ? FIND_WAY::NEAREST : FIND_WAY::NONE;
	}
}
