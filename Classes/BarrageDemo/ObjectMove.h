#pragma once
#ifndef __OBJECT_MOVE_H__
#define __OBJECT_MOVE_H__

#include "BarrageDemo\ObjectBase.h"

class ObjectMove : public ObjectBase
{
public :

	bool init(int id, int level);
	//�ƶ�,����false����Խ��Ӧ���Ƴ�
	virtual void move(float dt);

	virtual bool updateObj(float dt);

	float getSpeed() { return _speed; }
	void setSpeed(float speed) { _speed = speed; }

	int getRotate() { return _rotate; }
	void setRotate(int rotate) { _rotate = rotate; }

	void changeExtraDst(cocos2d::Vec2 dst) { _dst.extraValue += dst; }

	float getDamage() { return _damage; }
	virtual cocos2d::ValueMap& getInfo();
	cocos2d::Size getSpSize() { return _sp->getContentSize() * _sp->getScale(); }
protected:
	//ʵʱ����
	float _speed;
	float _damage;
	int _rotate;

	//ÿһ֡��Ŀ�ĵ���������ֵ������
	TwoValue<cocos2d::Vec2> _dst;
	cocos2d::Sprite* _sp;
};

#endif // !__OBJECT_MOVE_H__
