#pragma once
#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__
#include "cocos2d.h"

enum class DIRECTION
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class GameScene : public cocos2d::Scene
{
public :
	CREATE_FUNC(GameScene);
	bool init();
	void createPlayer();
	void createEnemies();
	//模拟武器发射,实际上是根据武器属性来发射
	void createBarrage(DIRECTION dir);
	void update(float dt);

	cocos2d::Node* getBullets() { return _bullets; }
	cocos2d::Node* getEnemies() { return _enemies; }
	cocos2d::Node* getPlayer() { return _player; }
private:
	cocos2d::Node* _bullets;
	cocos2d::Node* _enemies;
	cocos2d::Sprite* _player;
	cocos2d::Vector<cocos2d::Node*> _vecE;
};



#endif // !__GAME_SCENE_H__
