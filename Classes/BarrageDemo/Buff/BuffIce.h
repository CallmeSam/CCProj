#pragma once
#ifndef __BUFF_ICE_H__
#define __BUFF_ICE_H__
#include "BuffBase.h"

//��ǰ�ٶ� = �����ٶ� * _ratio
class BuffIce : public BuffBase
{
public :
	BuffIce(int id, int level , ObjectBase* owner);
	virtual void onBuffOccur();
	virtual void onBuffEnd();
	//��buff˯����ɺ���Ҫ���еĲ���
	virtual void buffAwake();
	virtual void refresh(int level);

	float getRatio() const { return _ratio; }
	virtual bool compareToOther(BuffBase* other);

private:
	float _ratio; 
};


#endif // !__BUFF_ICE_H__
