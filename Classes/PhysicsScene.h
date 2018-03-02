#pragma once
#ifndef  __PHYSICS_SCENE_H__
#define __PHYSICS_SCENE_H__
#include "cocos2d.h"
class PhysicsScene :public cocos2d::Scene
{
public:
	CREATE_FUNC(PhysicsScene);
	bool init();
	void update(float dt);
	void onEnter() override;
	void AboutCollisionBitmask();
	void AboutRayCast();
	bool callbackForRayCast(cocos2d::PhysicsWorld& world, const cocos2d::PhysicsRayCastInfo& info, void * data);

	float _angle;
	cocos2d::Size visibleSize;
	cocos2d::Sprite* sp;
	cocos2d::DrawNode* _node;
	cocos2d::DrawNode* _sphere;
};


#endif // ! __PHYSICS_SCENE_H__
