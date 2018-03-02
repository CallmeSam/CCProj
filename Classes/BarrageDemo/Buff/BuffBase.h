#pragma once
#ifndef __BUFF_BASE_H__
#define __BUFF_BASE_H__

struct BuffTime
{
	//�ӳٶ�ÿ�ʼ
	float delayTime;
	//�ܳ���ʱ��
	float totalTime;
	//����������һ��
	float interval;

	//Ԥ���ִֻ�п�ʼ�ͽ���
	static const BuffTime OneTick;
};



class ObjectBase;
class BuffBase
{
public:
	BuffBase();
	//buff��ʼ
	virtual void onBuffOccur();
	//buff����
	virtual void onBuffEnd();
	//buff����
	virtual void onBuffTick();
	//����
	virtual void update(float dt); 
	//ˢ��
	virtual void refresh(int level);
	//��ǿһ��
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
	//�Ƿ�ʼ
	bool _isBegin;
	//�Ƿ��ӳ�
	bool _isDelay;
	//�Ƿ����
	bool _aborted;
	//�Ƿ�����
	bool _isSleep;

	int _priority;
	BuffTime _time;
	//����ʱ��
	float _elapsed;
	//buff���õ�Ŀ��
	ObjectBase* _owner;
	//˭ʩ���buff
	ObjectBase* _sower;
};




#endif // !__BUFF_BASE_H__
