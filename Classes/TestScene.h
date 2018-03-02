#pragma once
#ifndef __TEST_SCENE_H__
#define __TEST_SCENE_H__
#include "cocos2d.h"
#include "ui\UIButton.h"

class TestScene : cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	CREATE_FUNC(TestScene);
	bool init();
	void AboutBoundingBox();
	void boundingTest(float dt);
	void run(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType type);
	void onEnter();

	void AboutWidget();
	void AboutSTLDeque();
	void AboutSTLMap();
	void AboutSTLSet();
	void AboutSTLFind();
	void AboutSTLFind_If();
	void AboutSTLFor_each();
	void AboutTemplate();
	void AboutArmature();
	void AboutUIButtonClick();
	void AboutJson();
	void AboutXml();
	void AboutFilePointer();
	void AboutPraseCSV();
	void AboutSwap();
	void AboutAudioEngine();
	void ScaleAndPos();
	void AboutClassAssignment();

	void AboutRecursiveJson();

	void testFormat();
	void testFilePointer();
	void testIOstream();
	void AboutSharedPtr();
	void AboutUniquePtr();
	void AboutWeakPtr();
	void AboutTools();
	void AboutLinkList();

	void testXml();

	void testForAdapt();

	void testForContact();
	void testForTC();

	void dumpPhysics();
	//??
	void AboutCameraAndRender();

	void AboutActionManager();

	void dumpOrCamera();

	void update(float dt);
public :
	bool _left;
	bool _right;
};

#endif // !__TEST_SCENE_H__
