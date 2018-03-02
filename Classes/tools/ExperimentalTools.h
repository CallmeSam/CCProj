#pragma once
#ifndef __EXPERIMENTAL_TOOLS_H__
#define __EXPERIMENTAL_TOOLS_H__
#include "cocos2d.h"
#include "ui/UIButton.h"
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

class ExperimentalTools
{
public:
	static std::string wstrToUTF8(const std::wstring& wstr);

	//通过符号来解析,需要解析的字符串，解析后的data，分隔符
	static void parseIntDataByMark(std::string str, std::vector<int>& data, const std::string& separator);

	//给节点创建一个外边框，空节点则无任何显示
	static void createOutline(cocos2d::Node* node, const cocos2d::Color4B& color);

	//给节点创建一个内边框
	static void createInline(cocos2d::Node* node, const cocos2d::Color4B& color);

	static void btnScaleEffect(cocos2d::ui::Button* btn, cocos2d::ui::Widget::TouchEventType type, float scale);
};


#endif // !__EXPERIMENTAL_TOOLS_H__