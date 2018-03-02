#pragma once
#ifndef __OBJECT_BASE_H__
#define __OBJECT_BASE_H__
#include "cocos2d.h"

template<typename T>
struct TwoValue
{
	T realValue = T();
	T extraValue = T();
};

enum class ObjectType
{
	NONE,
	ENEMY,
	PLAYER,
	BULLET
};

class BuffBase;
class ObjectBase : public cocos2d::Node
{
public :
	ObjectBase() :_id(0), _level(0), _isDead(false), _type(ObjectType::NONE){}
	~ObjectBase();
	//添加buff,sower传播者
	virtual void addBuff(int buffId, int level = 1, ObjectBase* sower = nullptr);
	//移除buff
	virtual std::multimap<std::string, BuffBase*>::iterator removeBuff(int buffId);
	virtual std::multimap<std::string, BuffBase*>::iterator removeBuff(std::multimap<std::string, BuffBase*>::iterator iter);

	virtual bool collideWithObject(ObjectBase* node);
	virtual void seperateWithObject(ObjectBase* node);
	//迭代自身buff所带来的影响
	virtual void updateBuff(float dt);

	//销毁
	virtual void destory();

	bool getIsDead() { return _isDead; }
	int getLv() { return _level; }
	ObjectType getObjType() { return _type; }
	int getId() { return _id; }
protected:
	int _id;
	int _level;
	bool _isDead;
	ObjectType _type;

	//施与他人的buff
	std::vector<int> _buffsTo;
	//自身拥有的buff
	std::multimap<std::string, BuffBase*> _buffsIn;
};


#endif // !__OBJECT_BASE_H__
