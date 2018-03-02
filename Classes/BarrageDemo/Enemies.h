#pragma once
#ifndef __ENEMIES_H__
#define __ENEMIES_H__
#include "ObjectMove.h"

class Enemies : public ObjectMove
{
public :
	static Enemies* createWithId(int enemyId, int level);
	bool init(int enemyId, int level);
	cocos2d::Size getSpSize() { return _sp->getContentSize() * _sp->getScale(); }
	cocos2d::ValueMap& getInfo();
	void getHurt(float damage);
	float getLife() { return _life; }
	virtual bool collideWithObject(ObjectBase* node);
private:
	float _life;
};



#endif // !__ENEMIES_H__
