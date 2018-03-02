#include "LeetCodeTest.h"
USING_NS_CC;

bool LeetCodeTest::init()
{
	if (!Scene::init())
		return false;

	log("HammingDistance: %d", HammingDistance461(1, 19));
	JudgeRouteCircle("UD");

	auto a = TreeNode(1);
	a.left = new TreeNode(3);
	a.right = new TreeNode(2);
	a.left->left = new TreeNode(5);

	auto b = TreeNode(2);
	b.left = new TreeNode(1);
	b.right = new TreeNode(3);
	b.left->right = new TreeNode(4);
	b.right->right = new TreeNode(7);

	auto c = MergeTwoBinaryTrees(&a, &b);

	NumberComplement(1);
	std::vector<std::string> aa{ "Hello", "Alaska", "Dad", "Peace" };
	KeyboardRow(aa);

	return true;
}

/*461*/
int LeetCodeTest::HammingDistance461(int x, int y)
{
	int bits = 0;
	//x和y都不为0的情况下结束循环
	while (x || y)
	{
		auto tailX = ((x >> 1) << 1) ^ x;
		auto tailY = ((y >> 1) << 1) ^ y;
		if (tailX ^ tailY)
			bits++;
		x = x >> 1;
		y = y >> 1;
	}

	return bits;
}

/*657*/
bool LeetCodeTest::JudgeRouteCircle(std::string moves)
{
	std::unordered_map<char, int> cmds;
	for (auto& cmd : moves)
	{
		switch (cmd)
		{
		case 'R':
		case 'L':
		case 'U':
		case 'D':
			cmds[cmd]++;
			break;
		default:
			return false;
			break;
		}
	}

	if ((cmds['R'] == cmds['L']) && (cmds['U'] == cmds['D']))
		return true;

	return false;
}

void recursiveNode(TreeNode* t1, TreeNode* t2, TreeNode* &root)
{
	if (!t1 && !t2)
		return;

	if (!t1)
	{
		root = t2;
		return;
	}
	if (!t2)
	{
		root = t1;
		return;
	}

	root = new TreeNode(t1->value + t2->value);
	recursiveNode(t1->left, t2->left, root->left);
	recursiveNode(t1->right, t2->right, root->right);
}

//617
TreeNode * LeetCodeTest::MergeTwoBinaryTrees(TreeNode * t1, TreeNode * t2)
{
	TreeNode* root = nullptr;
	recursiveNode(t1, t2, root);

	return root;
}

//476
int LeetCodeTest::NumberComplement(int num)
{
	if (num == 0)
		return 1;

	auto l = sizeof(num) * 8;
	int i = l - 1;
	for (; i >= 0; i--)
	{
		if (num >> i) break;
	}

	auto length = l - 1 - i;
	auto newNum = (~(num << length)) >> length;

	return 0;
}

//500
std::vector<std::string> LeetCodeTest::KeyboardRow(std::vector<std::string>& words)
{
	std::string s[3] = { "qwertyuiopQWERTYUIOP", "asdfghjklASDFGHJKL", "zxcvbnmZXCVBNM" };
	std::vector<std::string> outPut;
	for (auto& word : words)
	{
		auto character = word.at(0);
		auto i = 0;
		auto jump = false;
		for (; i < 3; i++)
		{
			auto iter = std::find(s[i].begin(), s[i].end(), character);
			if (iter != s[i].end())
				break;
		}
		for (auto j = 1; j < word.size(); j++)
		{
			auto iter = std::find(s[i].begin(), s[i].end(), word.at(j));
			if (iter == s[i].end())
			{
				jump = true;
				break;
			}
		}
		if (jump)
			continue;
		outPut.push_back(word);
	}

	
	return outPut;
}
