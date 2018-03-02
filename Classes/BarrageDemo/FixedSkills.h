#pragma once
#ifndef __FIXED_SKILLS_H__
#define __FIXED_SKILLS_H__
#include "Skills.h"

class FixedSkills : public Skills
{
public :
	static FixedSkills createWithSkillId(int skillId, int level, cocos2d::Node* weapon);
	bool init();

private:
	cocos2d::Node* weapon;
};



#endif // !__FIXED_SKILLS_H__
