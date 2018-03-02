#include "SkillFactory.h"
#include "SpecialSkills.h"
#include "BarrageDemo\Config\GameConfig.h"

Skills * SkillsFactory::createSkillWithId(int skillId, int level)
{
	auto info = SKILL_INFO[skillId - 1].asValueMap();
	auto interval = info["interval"].asFloat();
	if (interval == 0)
	{
		return Skills::createWithId(skillId, level);
	}
	else
	{
		return SpecialSkills::createWithId(skillId, level);
	}
}
