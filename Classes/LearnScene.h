#pragma once
#ifndef __LEARN_SCENE_H__
#define __LEARN_SCENE_H__

#include "cocos2d.h"

struct User
{
	int id;
	std::string username;
};

#define CREATE_FUNC_ONE(__TYPE__, __P_TYPE__) \
	static __TYPE__* createWithType(__P_TYPE__ __Type__)\
	{\
		auto pRet = new(std::nothrow) __TYPE__();\
		if(pRet && pRet->init(__Type__))\
		{\
			pRet->autorelease();\
			return pRet;\
		}\
		CC_SAFE_DELETE(pRet);\
		return nullptr;\
	}

class TypeNode : public cocos2d::Node
{
public:
	CREATE_FUNC_ONE(TypeNode, int);
	bool init(int) { return true; }
};


class LearnScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	CREATE_FUNC(LearnScene);
	bool init();

	void AboutParallexNode();
	void parallexMove(float dt);
	void AboutSimpleAudioEffect();
	void AboutBlend();
	void AboutFrameCallback();
	void AboutTemplate();
	void dump();
	void getRecFromZip();
	void aboutCsb();
	void aboutRemoveSelf();
	bool unCompress(const std::string& fileName, const std::string& passWord);
	void AboutHttp();
	void AboutWebSocket();
	void AboutZipFile();
	void AboutOperation();
	void AboutCopyConstructor();
	void AboutAllocator();
	void AboutStdMove();
	void AboutIOStream();
	void AboutSth();
	//node换层级，角度和坐标的变化
	void AboutRotAndPosTransmit();
	void AboutMacro();
	void About2DLight();
	void AboutSqlite();
	void AboutCallfunc();

	void callbackFunc();

	void update(float dt);

	std::unordered_map<int, User> _dataBase;
private:
	cocos2d::ParallaxNode* _parallex;
	cocos2d::Sprite* _sp;
	cocos2d::Sequence* _seq;
};



#endif