#pragma once
#ifndef __OBB_SCENE_H__
#define __OBB_SCENE_H__

#include "cocos2d.h"
class OBBScene : public cocos2d::Scene
{
public:
	CREATE_FUNC(OBBScene);
	bool init();

	void update(float dt);
public:
	cocos2d::Sprite* _sp_1;
	cocos2d::Sprite* _sp_2;
	cocos2d::DrawNode* _draw;
};

class Projection_2
{
public:
	Projection_2() :Projection_2(0, 0) {}
	Projection_2(float min, float max) : _min(min), _max(max) {}

	bool isOverlap(const Projection_2& proj);

	cocos2d::Vec2 axis;
	float _min;
	float _max;
};

class OBB_2
{
public:
	//counter clickwise
	OBB_2(const cocos2d::Vec2& center, float rotate, const cocos2d::Size& size);
	Projection_2 getProject(const cocos2d::Vec2& axis);
	bool isCollideWithOBB(OBB_2& obb);
public:
	cocos2d::Vec2 _vertex[4];
};





#endif // !__OBB_SCENE_H__



