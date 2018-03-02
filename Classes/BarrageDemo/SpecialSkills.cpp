#include "SpecialSkills.h"
#include "BarrageDemo\Config\GameConfig.h"

SpecialSkills * SpecialSkills::createWithId(int skillId, int level)
{
	auto skill = new(std::nothrow)SpecialSkills();
	if (skill && skill->init(skillId, level))
	{
		skill->autorelease();
		return skill;
	}
	CC_SAFE_DELETE(skill);
	return nullptr;
}

bool SpecialSkills::init(int skillId, int level)
{
	if (!Skills::init(skillId, level))
		return false;

	_isActive = true;
	auto &info = SKILL_INFO[skillId - 1].asValueMap();
	_interval = info["interval"].asFloat();
	_duration = info["duration"].asFloat();

	_objIn.clear();

	return true;
}

bool SpecialSkills::collideWithObject(ObjectBase * node)
{
	if (!Skills::collideWithObject(node))
		return false;

	_objIn.pushBack(node);

	return true;
}

void SpecialSkills::seperateWithObject(ObjectBase * node)
{
	_objIn.eraseObject(node);
}

void SpecialSkills::updateObjState(float dt)
{

	_elapsed += dt;

	while (_elapsed >= _interval)
	{
		_elapsed -= _interval;
	}

	if (_elapsed >= _duration)
	{
		_isActive = false;
	}
	else
	{
		_isActive = true;
	}
}

bool SpecialSkills::updateObj(float dt)
{
	if (!Skills::updateObj(dt))
		return false;

	updateObjState(dt);

	if (_isActive)
	{
		for (auto iter = _objIn.begin(); iter != _objIn.end();)
		{
			if ((*iter)->getIsDead())
			{
				iter = _objIn.erase(iter);
			}
			else
			{
				for (const auto& buff : _buffsTo)
				{
					cocos2d::log("buff id :%d", buff);
					(*iter)->addBuff(buff, _level, this);
				}

				iter++;
			}
		}
	}

	return true;
}
