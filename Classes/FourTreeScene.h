#pragma once
#ifndef __FOUR_TREE_SCENE_H__
#define __FOUR_TREE_SCENE_H__
#include "cocos2d.h"
#include <array>
#define COLLIDE_BODIES 100
#define DST_OBJECTS 500
#define COL 16
#define ROW 8

class QuadTree;
class FourTreeScene : public cocos2d::Scene
{
public:
	CREATE_FUNC(FourTreeScene);
	bool init();

	void AboutSpacePartition();
	void AboutQuadTree();

	void spacePartition();

	void collideWithObjects();

	void update(float dt);
	void updateForSpace();
	void updateForQuad();
	void updateForNormal();

	//根据点的位置来获取地图对应的位置
	cocos2d::Vec2 getPos(cocos2d::Vec2 point);
	void getVerts(const cocos2d::Rect& rect, cocos2d::Vec2* points);

public:
	bool _isPause;
	cocos2d::Sprite* _main[COLLIDE_BODIES];
	std::array<std::array<std::vector<cocos2d::Node*> , ROW>, COL> _map;
	std::vector<cocos2d::Node*> _resetNode;
	cocos2d::DrawNode* _drawNode;
	QuadTree* _tree;
	cocos2d::DrawNode* _drawOutline;
};

class QuadTree
{
public:
	static int MAX_OBJECTS;
	static int MAX_DEPTHS;

	QuadTree(int depth, cocos2d::Rect bound);
	~QuadTree();

	void insert(cocos2d::Node*);
	void split();
	void clear();
	void retrieve(const cocos2d::Rect& rect, std::vector<std::deque<cocos2d::Node*>>& list);
	int getIndex(const cocos2d::Rect& rect);

public:
	int _depth;
	QuadTree* _child[4];
	cocos2d::Rect _bound;
	std::deque<cocos2d::Node*> _root;
};







#endif // !__FOUR_TREE_SCENE_H__
