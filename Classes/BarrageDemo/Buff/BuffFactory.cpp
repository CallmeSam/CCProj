#include "BuffFactory.h"
#include "BarrageDemo\Config\GameConfig.h"
#include "BuffIce.h"
#include "BuffHurt.h"
#include "BuffForce.h"
#include "BuffAim.h"
#include "BuffIce.h"
#include "BuffRotate.h"
#include "BarrageDemo\ObjectBase.h"

BuffBase * BuffFactory::createBuffWithId(int id, ObjectBase* owner, int level, ObjectBase* sower)
{
	BuffBase* ptr = nullptr;
	auto info = BUFF_INFO[id - 1].asValueMap();
	auto name = info["name"].asString();
	if (name == "ice")
	{
		ptr = new BuffIce(id, level, owner);
	}
	else if (name == "hurt")
	{
		ptr = new BuffHurt(id, level, owner);
	}
	else if (name == "force" && sower)
	{
		auto sowerId = sower->getId();
		//震荡波的buff有些不同
		if (sowerId == 7)
		{
			ptr = new BuffForce(id, level, owner, -sower->getRotation() + 90);
		}
		else
		{
			ptr = new BuffForce(id, level, owner, sower->getPosition());
		}
	}
	else if (name == "aim")
	{
		ptr = new BuffAim(id, level, owner);
	}
	else if (name == "angular")
	{
		ptr = new BuffRotate(id, level, owner);
	}

	return ptr;
}
