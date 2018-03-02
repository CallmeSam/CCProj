#pragma once
#ifndef __BUFF_ROTATE_H__
#define __BUFF_ROTATE_H__
#include "BuffBase.h"

class BuffRotate : public BuffBase
{
public:
	BuffRotate(int id, int level, ObjectBase* owner);
	virtual void onBuffOccur();
	virtual void onBuffEnd();
	virtual void buffAwake();
	void refresh(int level);

	int getRotate() const { return _rotate; }
	virtual bool compareToOther(BuffBase* other);

private:
	int _rotate;
};


#endif // !__BUFF_ROTATE_H__
