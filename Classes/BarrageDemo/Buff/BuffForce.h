#pragma once
#ifndef __BUFF_FORCE_H__
#define __BUFF_FORCE_H__
#include "BuffBase.h"
#include "cocos2d.h"

class BuffForce : public BuffBase
{
public :
	BuffForce(int id, int level, ObjectBase* owner);
	BuffForce(int id, int level, ObjectBase* owner, cocos2d::Vec2 dst);
	BuffForce(int id, int level, ObjectBase* owner, float dir);
	virtual void onBuffOccur();
	virtual void onBuffTick();

	float getForce() const { return _force; }
	virtual bool compareToOther(BuffBase* other);
	virtual void refresh(int level);
private:
	cocos2d::Vec2 _dst;
	float _force;
	float _range;
	float _dir;
	//那个方向拉动
	bool _isUseDir;
};




#endif // !__BUFF_FORCE_H__
