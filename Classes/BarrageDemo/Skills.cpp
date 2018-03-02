#include "Skills.h"
#include "BarrageDemo\Config\GameConfig.h"
#include "SkillFactory.h"

USING_NS_CC;
Skills * Skills::createWithId(int id, int level)
{
	auto skill = new(std::nothrow)Skills();
	if (skill && skill->init(id, level))
	{
		skill->autorelease();
		return skill;
	}
	CC_SAFE_DELETE(skill);
	return nullptr;
}

bool Skills::init(int skillId, int level)
{
	if (!ObjectMove::init(skillId, level))
		return false;

	_type = ObjectType::BULLET;
	_isPierce = false;
	_brokenEffects.clear();

	//加载技能数据
	auto &info = SKILL_INFO[skillId - 1].asValueMap();
	auto upgradeInfo = info["upgrade"].asValueMap();
	//属性的增加 = 初始  + （等级 - 1） * 增率
	_speed = info["speed"].asFloat() + upgradeInfo["speed"].asFloat() * (level - 1);
	_distance = info["distance"].asFloat() + upgradeInfo["distance"].asFloat() * (level - 1);
	_isUseDis = _distance == 0.f ? false : true;
	_aliveTime = info["aliveTime"].asFloat()  + upgradeInfo["aliveTime"].asFloat() * (level - 1);
	_isUseTime = _aliveTime == 0.f ? false : true;
	_damage = info["damage"].asFloat() + upgradeInfo["damage"].asFloat() * (level - 1);
	_isPierce = info["pierce"].asBool();

	auto scale = info["scale"].asFloat() + upgradeInfo["scale"].asFloat() * (level - 1);
	_sp = Sprite::create(info["pic"].asString());
	_sp->setScale(1 + scale);
	addChild(_sp);

	//physicsBody
	auto physicsBody = PhysicsBody::createBox(getSpSize());
	physicsBody->setCategoryBitmask(BULLET_CATEGORY_MASK);
	physicsBody->setCollisionBitmask(0);
	physicsBody->setContactTestBitmask(BULLET_CONTACT_MASK);
	this->addComponent(physicsBody);

	//buff
	if (!info["buff"].isNull())
	{
		auto &buffs = info["buff"].asValueVector();
		for (auto &buff : buffs)
			this->addBuff(buff.asInt(), _level);
	}

	if (!info["effect"].isNull())
	{
		auto &buffsTo = info["effect"].asValueVector();
		for (auto &buff : buffsTo)
			_buffsTo.push_back(buff.asInt());
	}

	if (!info["broken"].isNull())
	{
		auto &skills = info["broken"].asValueVector();
		_brokenEffects = skills;
	}

	return true;
}

void Skills::move(float dt)
{
	ObjectMove::move(dt);

	_distance -= _speed * dt;

	if (_isUseDis && _distance <= 0)
		_isDead = true;
}

bool Skills::collideWithObject(ObjectBase * node)
{
	//增加buff
	if (!ObjectMove::collideWithObject(node))
		return false;

	if (!_isPierce)
	{
		_isDead = true;
		return false;
	}
	
	return true;
}


cocos2d::ValueMap& Skills::getInfo()
{
	return SKILL_INFO[_id - 1].asValueMap();
}

bool Skills::updateObj(float dt)
{
	if (!_isDead && _isUseTime)
	{
		_aliveTime -= dt;
		_isDead = _aliveTime <= 0 ? true : false;
	}

	return ObjectMove::updateObj(dt);
}

void Skills::destory()
{
	if (!_brokenEffects.empty())
	{
		auto parent = this->getParent();
		for (auto & info : _brokenEffects)
		{
			auto id = info.asValueMap()["id"].asInt();
			Skills* skill = SkillsFactory::createSkillWithId(id, _level);
			auto pos = info.asValueMap()["offset"].asString();
			auto x = atoi(pos.substr(0, pos.find(",")).c_str());
			auto y = atoi(pos.substr(pos.find(",") + 1).c_str());
			skill->setPosition(this->getPosition() + Vec2(x, y));
			parent->addChild(skill);
		}
	}

	ObjectMove::destory();
}

