#pragma once
#ifndef __BUFF_BASE_H__
#define __BUFF_BASE_H__

struct BuffTime
{
	//延迟多久开始
	float delayTime;
	//总持续时间
	float totalTime;
	//间隔多久作用一次
	float interval;

	//预设的只执行开始和结束
	static const BuffTime OneTick;
};



class ObjectBase;
class BuffBase
{
public:
	BuffBase();
	//buff开始
	virtual void onBuffOccur();
	//buff结束
	virtual void onBuffEnd();
	//buff到点
	virtual void onBuffTick();
	//迭代
	virtual void update(float dt); 
	//刷新
	virtual void refresh(int level);
	//增强一级
	virtual void addLV();

	virtual void buffAwake();

	virtual bool compareToOther(BuffBase* other);

	virtual void destory();

	bool getIsSleep() { return _isSleep; }
	void setBuffSleep(bool isSleep);
	bool getIsOver() { return _aborted; }
	int getID() { return _id; }
protected:
	int _id;
	//是否开始
	bool _isBegin;
	//是否延迟
	bool _isDelay;
	//是否结束
	bool _aborted;
	//是否隐藏
	bool _isSleep;

	int _priority;
	BuffTime _time;
	//过的时间
	float _elapsed;
	//buff作用的目标
	ObjectBase* _owner;
	//谁施与的buff
	ObjectBase* _sower;
};




#endif // !__BUFF_BASE_H__
