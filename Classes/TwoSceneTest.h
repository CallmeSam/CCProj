#pragma once
#ifndef __TWO_SCENE_TEST_H__
#define __TWO_SCENE_TEST_H__
#include "cocos2d.h"

class FirstScene : public cocos2d::Scene
{
public:
	CREATE_FUNC(FirstScene);
	bool init();

	void AboutParent();

	void AboutScheduleLamda();

	void AboutConvert();

	void AboutOpacity();

	void AboutEmptyTexture();

	void AboutLayer();

	void AboutLayerSetTouchEnable();

	void AboutTimelineEfficiency();

	void AboutAStarPath();

	void AboutClippingNodePos();

	void AboutCommand();
	virtual void visit(cocos2d::Renderer* render, const cocos2d::Mat4& parentTransform, std::uint32_t parentFlags) override;
	void onDraw();

private:
	cocos2d::CustomCommand _command;
};

class SecondScene : public cocos2d::Scene
{
public:
	CREATE_FUNC(SecondScene);
	bool init();
};





#endif // !__TWO_SCENE_TEST_H__
