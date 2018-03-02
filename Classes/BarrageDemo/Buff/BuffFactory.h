#pragma once
#ifndef __BUFF_FACTORY_H__
#define __BUFF_FACTORY_H__
#include "BuffBase.h"
#include <string>

class ObjectBase;
class BuffFactory
{
public:
	static BuffBase* createBuffWithId(int id, ObjectBase* owner,  int level = 1, ObjectBase* sower = nullptr);
};



#endif // !__BUFF_FACTORY_H__
