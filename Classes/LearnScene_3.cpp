#include "LearnScene_3.h"

bool LearnScene_3::init()
{
	if(!Scene::init())
		return false;

	cppMemoryLayout();

	return true;
}

struct A 
{
	char c;
	int i;
};

void LearnScene_3::cppMemoryLayout()
{
	size_t aSize = sizeof(A);
	A a;
	void* add_1 = &a;
	void* add_2 = &(a.c);


	return;
}
