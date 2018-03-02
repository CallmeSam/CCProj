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
	//���buff,sower������
	virtual void addBuff(int buffId, int level = 1, ObjectBase* sower = nullptr);
	//�Ƴ�buff
	virtual std::multimap<std::string, BuffBase*>::iterator removeBuff(int buffId);
	virtual std::multimap<std::string, BuffBase*>::iterator removeBuff(std::multimap<std::string, BuffBase*>::iterator iter);

	virtual bool collideWithObject(ObjectBase* node);
	virtual void seperateWithObject(ObjectBase* node);
	//��������buff��������Ӱ��
	virtual void updateBuff(float dt);

	//����
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

	//ʩ�����˵�buff
	std::vector<int> _buffsTo;
	//����ӵ�е�buff
	std::multimap<std::string, BuffBase*> _buffsIn;
};


#endif // !__OBJECT_BASE_H__
