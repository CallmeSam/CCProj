#include "ObjectBase.h"
#include "Buff\BuffFactory.h"
#include "BarrageDemo\Config\GameConfig.h"

ObjectBase::~ObjectBase()
{
	for (auto &iter : _buffsIn)
	{
		iter.second->destory();
	}
}

/*��ӵ��߼���
	�ҵ������ֵ�buff�����������������бȽϣ�������ӵ�������������ͬ����buff����˯�ߣ������Լ�˯��;
	������id�Ľ���ˢ�¡�
	��û��������ֱ�ӽ������buff
*/
void ObjectBase::addBuff(int buffId, int level, ObjectBase* sower)
{
	auto buff = BuffFactory::createBuffWithId(buffId, this, level, sower);
	assert(buff);
	auto name = BUFF_INFO[buffId - 1].asValueMap()["name"].asString();
	std::vector < BuffBase*> orderBuff;
	auto iters = _buffsIn.equal_range(name);
	if (iters.first == iters.second)
	{
		buff->setBuffSleep(false);
		_buffsIn.insert(std::make_pair(name, buff));
	}
	else
	{
		bool refresh = false;
		for (auto iter = iters.first; iter != iters.second; iter++)
		{
			orderBuff.push_back(iter->second);
			if (iter->second->getID() == buffId)
			{
				iter->second->refresh(level);
				refresh = true;
			}
		}

		std::sort(orderBuff.begin(), orderBuff.end(), 
			[](BuffBase* b1, BuffBase* b2) 
		{
			return b1->compareToOther(b2);
		});

		if (refresh)
			return;

		auto back = *(orderBuff.rbegin());
		if (buff->compareToOther(back))
		{
			buff->setBuffSleep(true);
		}
		else
		{
			buff->setBuffSleep(false);
			back->setBuffSleep(true);
		}

		_buffsIn.insert(std::make_pair(name, buff));
	}
}

/*
����id�ҵ���ǰbuff�������ǰbuff��sleep״̬��ֱ���Ƴ���
������ͬ����buff������һ�����ֵ��buff���Ƴ���ǰbuff
*/
std::multimap<std::string, BuffBase*>::iterator ObjectBase::removeBuff(int buffId)
{
	auto name = BUFF_INFO[buffId - 1].asValueMap()["name"].asString();
	auto iters = _buffsIn.equal_range(name);
	if (iters.first == iters.second)
	{
		return _buffsIn.end();
	}
	else
	{
		std::set<BuffBase*> orderBuff;
		std::multimap<std::string, BuffBase*>::iterator deleteIter;

		for (auto iter = iters.first; iter != iters.second; iter++)
		{
			if (iter->second->getID() == buffId)
			{
				deleteIter = iter;
			}
			else
			{
				orderBuff.insert(iter->second);
			}
		}

		auto isSleep = deleteIter->second->getIsSleep();
		if (isSleep)
		{
			deleteIter->second->destory();
			return _buffsIn.erase(deleteIter);
		}
		else
		{
			if (orderBuff.size() != 0)
			{
				for (auto iter = orderBuff.begin(); iter != orderBuff.end(); iter++)
				{
					if (iter == (--orderBuff.end()))
					{
						(*iter)->setBuffSleep(false);
					}
					else
					{
						(*iter)->setBuffSleep(true);
					}
				}
			}

			deleteIter->second->destory();
			return _buffsIn.erase(deleteIter);
		}
	}
}

std::multimap<std::string, BuffBase*>::iterator ObjectBase::removeBuff(std::multimap<std::string, BuffBase*>::iterator iter)
{
	return removeBuff(iter->second->getID());
}

bool ObjectBase::collideWithObject(ObjectBase* node)
{
	if (_isDead || !node)
		return false;

	for (const auto& buffId : _buffsTo)
	{
		//�ȼ�,�Ƿ�������ĵȼ�
		node->addBuff(buffId, _level, this);
	}

	return true;
}

void ObjectBase::seperateWithObject(ObjectBase * node)
{

}

void ObjectBase::updateBuff(float dt)
{
	for (auto iter = _buffsIn.begin(); iter != _buffsIn.end();)
	{
		if (iter->second->getIsOver())
		{
			iter = removeBuff(iter);
		}
		else
		{
			iter->second->update(dt);
			if (iter->second->getIsOver())
			{
				iter = removeBuff(iter);
			}
			else
				iter++;
		}
	}
}

void ObjectBase::destory()
{

}
