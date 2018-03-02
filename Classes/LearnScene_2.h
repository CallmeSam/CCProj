#pragma once
#ifndef __LEARN_SCENE_2_H__
#define __LEARN_SCENE_2_H__
#include "cocos2d.h"

struct PointInfo
{
	int g;
	int h;
	PointInfo* parent;
	cocos2d::Vec2 coordinate;
};

class ticket
{
public:
	ticket();

	void myThreadA();

	void myThreadB();

	int n;
	std::mutex mutex;
};

class TrackPart : public cocos2d::Node
{
public:
	std::deque<std::pair<cocos2d::Vec2, float>> _track;
	float _distance;
	TrackPart* _bro;
	void move();
	void refreshTrack(const std::pair<cocos2d::Vec2, float>& broInfo);
};

class Track : public cocos2d::Node
{
public:
	void addTrack(TrackPart* track);
};

class RibbonTrail;
class LearnScene_2 : public cocos2d::Scene
{
public:
	CREATE_FUNC(LearnScene_2);
	bool init();

	void AboutChrono();
	void AboutTime_t();
	void AboutAStart();
	void AboutWStrToUTF8();
	void AboutShader();
	void AboutRenderTexture();
	void AboutTransitionScene();
	void AboutIO();
	void AboutSpine();
	void AboutPageView();
	void AboutThread();
	void AboutMissile();
	void AboutMotionStreak();
	void AboutOutline();
	void AboutShaderOutline();
	void AboutGif();
	void AboutWriteXML();
	//A*
	void putPointIntoCloseList(PointInfo* node);
	void checkAroundToFindShortestNode(PointInfo* node);
	void getAroundPointInfo(PointInfo* parent);
	void showRoute(PointInfo* endPoint);
private:
	//A*
	std::vector<PointInfo*> openList;
	std::vector<PointInfo*> closeList;
	cocos2d::Vec2 begin;
	cocos2d::Vec2 destination;
	std::vector<cocos2d::Vec2>obstacle;

	ticket* t;

	RibbonTrail* m_pRainbow;
	float m_fTime;
	cocos2d::Vec3 m_fDirDist;
};

class P_TransitionScene : public cocos2d::TransitionScene
{
public:
	static P_TransitionScene * create(float t, Scene *scene);
	void onEnter();
private:
	float _time;
};




#endif // !__LEARN_SCENE_2_H__

