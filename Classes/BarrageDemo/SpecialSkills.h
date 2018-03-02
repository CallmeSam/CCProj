#pragma once
#ifndef __SPECIAL_SKILLS_H__
#define __SPECIAL_SKILLS_H__
#include "BarrageDemo\Skills.h"
/*
���⼼�ܣ�����һ����־���ڿ���skill�е�buff�ͷţ�
��skill�е�buff�ص㶼��ֻ����һ֡��ʱ�䣬
��Ϊ��skillÿ֡�������buff�����־��Ч״̬
*/
class SpecialSkills : public Skills
{
public :
	static SpecialSkills* createWithId(int skillId, int level = 1);
	bool init(int skillId, int level);
	virtual bool collideWithObject(ObjectBase* node);
	virtual void seperateWithObject(ObjectBase* node);
	void updateObjState(float dt);
	virtual bool updateObj(float dt);
private:
	//�Ƿ񼤻������ÿ֡�����addbuff
	bool _isActive;
	//ÿ����ÿ�ʼ����
	float _interval;
	//ÿ������ʱ��
	float _duration;
	//����ʱ��
	float _elapsed;
	//������skill�е�obj
	cocos2d::Vector<ObjectBase*> _objIn;
};




#endif // !__SPECIAL_SKILLS_H__
