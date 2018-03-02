#pragma once
#ifndef __SKILL_FACTORY_H__
#define __SKILL_FACTORY_H__

class Skills;
class SkillsFactory
{
public:
	static Skills* createSkillWithId(int skillId, int level = 1);
};


#endif