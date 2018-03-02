#pragma once
#ifndef __BUFF_HURT_H__
#define __BUFF_HURT_H__
#include "BuffBase.h"

class BuffHurt : public BuffBase
{
public:
	BuffHurt(int id, int level, ObjectBase* owner);
	virtual void onBuffOccur();
	virtual void onBuffTick();

	float getDamage() const { return _life; }
	virtual bool compareToOther(BuffBase* other);

	virtual void refresh(int level);
private:
	int _life;
};



#endif // !__BUFF_HURT_H__
