#pragma once
#ifndef __SKILLS_H__
#define __SKILLS_H__

#include "ObjectMove.h"

class Skills : public ObjectMove
{
public:
	static Skills* createWithId(int skillId, int level = 1);
	virtual bool init(int id, int level);
	virtual void move(float dt);
	virtual bool collideWithObject(ObjectBase* node);
	cocos2d::ValueMap& getInfo();
	virtual bool updateObj(float dt);
	virtual void destory();
protected:
	bool _isPierce;
	//死亡方式使用哪一种
	bool _isUseDis;
	bool _isUseTime;
	float _distance;
	float _aliveTime;
	cocos2d::ValueVector _brokenEffects;
};


#endif // !__SKILLS_H__
