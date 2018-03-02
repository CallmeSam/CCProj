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

	//ͨ������������,��Ҫ�������ַ������������data���ָ���
	static void parseIntDataByMark(std::string str, std::vector<int>& data, const std::string& separator);

	//���ڵ㴴��һ����߿򣬿սڵ������κ���ʾ
	static void createOutline(cocos2d::Node* node, const cocos2d::Color4B& color);

	//���ڵ㴴��һ���ڱ߿�
	static void createInline(cocos2d::Node* node, const cocos2d::Color4B& color);

	static void btnScaleEffect(cocos2d::ui::Button* btn, cocos2d::ui::Widget::TouchEventType type, float scale);
};


#endif // !__EXPERIMENTAL_TOOLS_H__