#pragma once
#ifndef __BUFF_AIM_H__
#define __BUFF_AIM_H__
#include "BuffBase.h"
#include "BarrageDemo\ObjectBase.h"

enum class FIND_TYPE
{
	NONE,
	ENEMY,
	BULLET,
	PLAYER
};

enum class FIND_WAY
{
	NONE,
	RANDOM,
	NEAREST
};


class BuffAim : public BuffBase
{
public :
	BuffAim(int id, int level, ObjectBase* owner);
	void towardToObject(cocos2d::Node* obj, int rotate);
	virtual void onBuffOccur();
	virtual void onBuffTick();
	virtual void refresh(int level);
private:
	FIND_TYPE _type;
	FIND_WAY _way;
	int _targetTag;
};


#endif // !__BUFF_AIM_H__
