#pragma once
#ifndef __SPECIAL_SKILLS_H__
#define __SPECIAL_SKILLS_H__
#include "BarrageDemo\Skills.h"
/*
特殊技能：存在一个标志用于控制skill中的buff释放，
此skill中的buff特点都是只存在一帧的时间，
因为此skill每帧都是添加buff如果标志生效状态
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
	//是否激活，如果激活，每帧则调用addbuff
	bool _isActive;
	//每隔多久开始作用
	float _interval;
	//每次作用时长
	float _duration;
	//流逝时间
	float _elapsed;
	//包含在skill中的obj
	cocos2d::Vector<ObjectBase*> _objIn;
};




#endif // !__SPECIAL_SKILLS_H__
