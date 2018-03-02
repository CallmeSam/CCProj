#pragma once
#ifndef __BARRAGE_SCENE_H__
#define __BARRAGE_SCENE_H__
#include "cocos2d.h"
#define COL 16
#define ROW 8

class BarrageScene : public cocos2d::Scene
{
public:
	CREATE_FUNC(BarrageScene);
	bool init();

	void createBarrage();
	void createPlayer();
	cocos2d::Sprite* createEnemy();
	void addEnemyToPool();

	void moveTowardsPlayer(cocos2d::Node* node);

	void spacePartition(std::array<std::array<std::vector<cocos2d::Node*>, ROW>, COL>& map);
	void collideWithObjects(std::array<std::array<std::vector<cocos2d::Node*>, ROW>, COL>& map, std::vector<cocos2d::Node*>& deleteList);
	cocos2d::Vec2 getPos(cocos2d::Vec2 point);
	void getVerts(const cocos2d::Rect& rect, cocos2d::Vec2* points);

	void update(float dt);
public:
	cocos2d::Node* _bullets;
	cocos2d::Node* _enemies;
	cocos2d::Sprite* _player;
	cocos2d::Vector<cocos2d::Sprite*> _enemyPool;
};


#endif // !__BARRAGE_SCENE_H__
