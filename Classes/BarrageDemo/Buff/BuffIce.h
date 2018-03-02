#pragma once
#ifndef __BUFF_ICE_H__
#define __BUFF_ICE_H__
#include "BuffBase.h"

//当前速度 = 基础速度 * _ratio
class BuffIce : public BuffBase
{
public :
	BuffIce(int id, int level , ObjectBase* owner);
	virtual void onBuffOccur();
	virtual void onBuffEnd();
	//当buff睡眠完成后，需要进行的操作
	virtual void buffAwake();
	virtual void refresh(int level);

	float getRatio() const { return _ratio; }
	virtual bool compareToOther(BuffBase* other);

private:
	float _ratio; 
};


#endif // !__BUFF_ICE_H__
