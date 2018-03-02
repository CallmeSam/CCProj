#pragma once
#ifndef __LEET_CODE_TEST_H__
#define __LEET_CODE_TEST_H__
#include "cocos2d.h"

class TreeNode
{
public:
	TreeNode(int x) :value(x), left(nullptr), right(nullptr) {}
	int value;
	TreeNode* left;
	TreeNode* right;
};

class LeetCodeTest : public cocos2d::Scene
{
public:
	CREATE_FUNC(LeetCodeTest);
	bool init() override;

	int HammingDistance461(int x, int y);
	bool JudgeRouteCircle(std::string moves);
	TreeNode* MergeTwoBinaryTrees(TreeNode* t1, TreeNode* t2);
	int NumberComplement(int num);
	std::vector<std::string> KeyboardRow(std::vector<std::string>& words);
};


#endif // !__LEET_CODE_TEST_H__
