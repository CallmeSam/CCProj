#include "FourTreeScene.h"
#include "ui\UIButton.h"

#undef CC_PROFILER_DISPLAY_TIMERS
#define CC_PROFILER_DISPLAY_TIMERS() Profiler::getInstance()->displayTimers()
#undef CC_PROFILER_PURGE_ALL
#define CC_PROFILER_PURGE_ALL() Profiler::getInstance()->releaseAllTimers()

#undef CC_PROFILER_START
#define CC_PROFILER_START(__name__) ProfilingBeginTimingBlock(__name__)
#undef CC_PROFILER_STOP
#define CC_PROFILER_STOP(__name__) ProfilingEndTimingBlock(__name__)

USING_NS_CC;

bool FourTreeScene::init()
{
	if (!Scene::init())
		return false;
	
	AboutSpacePartition();
	//AboutQuadTree();

	_drawOutline = DrawNode::create();
	this->addChild(_drawOutline);

	_isPause = false;
	for (auto i = 0; i < COLLIDE_BODIES; i++)
	{
		_main[i] = Sprite::create("CloseNormal.png");
		addChild(_main[i]);
	}
	scheduleUpdate();

	auto btn = ui::Button::create("brokenBrick.png");
	addChild(btn);
	btn->addTouchEventListener([this](Ref*, ui::Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			if (_isPause)
			{
				this->scheduleUpdate();
				this->_isPause = false;
			}
			else
			{
				CC_PROFILER_DISPLAY_TIMERS();
				this->unscheduleUpdate();
				this->_isPause = true;
			}
		}
	});

	btn->setOpacity(100);
	btn->setPosition(Vec2(100, 100));

	return true;
}

void FourTreeScene::AboutSpacePartition()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	for (auto i = 0; i < DST_OBJECTS; i++)
	{
		auto sp = Sprite::create("tree2.png");
		sp->setPosition(rand_0_1() * visibleSize.width, rand_0_1() * visibleSize.height);
		addChild(sp);
	}

	spacePartition();

	auto btn = ui::Button::create("brokenBrick.png");
	addChild(btn);
	btn->addTouchEventListener([this](Ref*, ui::Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			auto visible = this->_drawOutline->isVisible();
			this->_drawOutline->setVisible(!visible);
		}
	});

	btn->setOpacity(150);
	btn->setPosition(Vec2(400, 100));
	//CC_PROFILER_STOP("create");

	//CC_PROFILER_DISPLAY_TIMERS();
}

void FourTreeScene::AboutQuadTree()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	_drawNode = DrawNode::create();
	_drawNode->setName("draw");
	_drawNode->setAnchorPoint(Vec2::ZERO);
	addChild(_drawNode, 10);

	_tree = new QuadTree(0, Rect(Vec2::ZERO, visibleSize));

	for (auto i = 0; i < DST_OBJECTS; i++)
	{
		auto sp = Sprite::create("paw.png");
		sp->setPosition(rand_0_1() * visibleSize.width, rand_0_1() * visibleSize.height);
		addChild(sp);

		_tree->insert(sp);
	}
}

void FourTreeScene::spacePartition()
{
	CC_PROFILER_START("partition:");
	for (const auto &child : this->getChildren())
	{
		auto rect = child->getBoundingBox();
		Vec2 point[4];
		this->getVerts(rect, point);
		//获得最小和最大点，在这个范围中遍历
		auto min = getPos(point[0]);
		auto max = getPos(point[3]);
		//区域外的不做碰撞处理
		for (auto i = min.x; i <= max.x; i++)
		{
			if (i < 0 || i > COL - 1)
				continue;
			for (auto j = min.y; j <= max.y; j++)
			{
				if (j < 0 || j > ROW - 1)
					continue;

				_map[i][j].push_back(child);

			}
		}
	}
	CC_PROFILER_STOP("partition:");
	CC_PROFILER_DISPLAY_TIMERS();
}

cocos2d::Vec2 FourTreeScene::getPos(cocos2d::Vec2 point)
{
	auto col = floor(point.x / 60);
	auto row = floor(point.y / 90);

	return Vec2(col, row);
}

void FourTreeScene::getVerts(const cocos2d::Rect & rect, cocos2d::Vec2 * points)
{
	points[0] = rect.origin;
	points[1] = rect.origin + Vec2(rect.size.width, 0);
	points[2] = rect.origin + Vec2(0, rect.size.height);
	points[3] = rect.origin + rect.size;
}

void FourTreeScene::collideWithObjects()
{
	for (auto i = 0; i < COLLIDE_BODIES; i++)
	{
		auto boundBox = _main[i]->getBoundingBox();
		
		Vec2 verts[4];
		this->getVerts(boundBox, verts);
		//获得最小和最大点，在这个范围中遍历
		auto min = getPos(verts[0]);
		auto max = getPos(verts[3]);
		//区域外的不做碰撞处理
		for (auto i = min.x; i <= max.x; i++)
		{
			if (i < 0 || i >	COL - 1)
				continue;
			for (auto j = min.y; j <= max.y; j++)
			{
				if (j < 0 || j > ROW - 1)
					continue;

				for (const auto& child : _map[i][j])
				{
					if (child->getColor() == Color3B::WHITE && child->getBoundingBox().intersectsRect(boundBox))
					{

						_drawOutline->drawRect(boundBox.origin, boundBox.origin + boundBox.size, Color4F::GREEN);
						auto bbox = child->getBoundingBox();
						_drawOutline->drawRect(bbox.origin, bbox.origin + bbox.size, Color4F::MAGENTA);

						child->setColor(Color3B::RED);
						_resetNode.push_back(child);
					}
				}
			}
		}
	}
}

void FourTreeScene::update(float dt)
{
	_drawOutline->clear();
	for (const auto& child : _resetNode)
	{
		child->setColor(Color3B::WHITE);
	}
	_resetNode.clear();
	CC_PROFILER_START("COLLIDE");
	//updateForQuad();
	updateForSpace();
	//updateForNormal();
	CC_PROFILER_STOP("COLLIDE");
}

void FourTreeScene::updateForSpace()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	for (auto i = 0; i < COLLIDE_BODIES; i++)
		_main[i]->setPosition(rand_0_1() * visibleSize.width, rand_0_1() * visibleSize.height);
	collideWithObjects();
}

void FourTreeScene::updateForQuad()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	std::vector<std::deque<cocos2d::Node*>> vecDeqNode;
	auto index = 0;
	for (auto i = 0; i < COLLIDE_BODIES; i++)
	{
		_main[i]->setPosition(rand_0_1() * visibleSize.width, rand_0_1() * visibleSize.height);
		CC_PROFILER_START("RETRIEVE");
		_tree->retrieve(_main[i]->getBoundingBox(), vecDeqNode);
		CC_PROFILER_STOP("RETRIEVE");

		CC_PROFILER_START("ITERATOR");

		for (; index < vecDeqNode.size(); index++)
		{
			for (auto& child : vecDeqNode[index])
			{
				if (child->getColor() == Color3B::WHITE && child->getBoundingBox().intersectsRect(_main[i]->getBoundingBox()))
				{
					child->setColor(Color3B::RED);
					_resetNode.push_back(child);
				}
			}
		}
		CC_PROFILER_STOP("ITERATOR");
	}
}

void FourTreeScene::updateForNormal()
{
}

void QuadTree::insert(cocos2d::Node * node)
{
	if (!node)
		return;
	
	if (_child[0])
	{
		auto bound = node->getBoundingBox();
		auto index = getIndex(bound);
		if (index != -1)
		{
			_child[index]->insert(node);
			return;
		}
	}
	_root.push_back(node);
	if (_depth < QuadTree::MAX_DEPTHS && _root.size() > QuadTree::MAX_OBJECTS)
	{
		split();
		auto size = _root.size();
		for (auto i = 0; i < size; i++)
		{
			auto back = _root.back();
			_root.pop_back();
			auto index = getIndex(back->getBoundingBox());
			if (index == -1)
				_root.push_front(back);
			else
				_child[index]->insert(back);
		}
	}

}

int QuadTree::MAX_OBJECTS = 10;
int QuadTree::MAX_DEPTHS = 5;

void QuadTree::split()
{
	if (_child[0])
		return;

	cocos2d::Rect rect[4];
	rect[0] = Rect(_bound.origin + _bound.size / 2, _bound.size / 2);
	rect[1] = Rect(Vec2(_bound.origin.x, _bound.origin.y + _bound.size.height / 2), _bound.size / 2);
	rect[2] = Rect(_bound.origin, _bound.size / 2);
	rect[3] = Rect(Vec2(_bound.origin.x + _bound.size.width / 2, _bound.origin.y), _bound.size / 2);

	for (auto i = 0; i < 4; i++)
	{
		_child[i] = new QuadTree(_depth + 1, rect[i]);
		_root[0]->getParent()->getChildByName<cocos2d::DrawNode*>("draw")->drawRect(rect[i].origin, rect[i].origin + rect[i].size, Color4F::WHITE);
	}
}

void QuadTree::retrieve(const cocos2d::Rect& rect, std::vector<std::deque<Node*>>& list)
{
	auto index = getIndex(rect);

	if (_child[0] && index != -1)
	{
		_child[index]->retrieve(rect, list);
	}
	
	if (_root.size() > 0)
	{
		list.push_back(_root);
	}
}

int QuadTree::getIndex(const cocos2d::Rect & rect)
{
	auto isBottom = rect.getMinY() < _bound.getMidY() && rect.getMaxY() <= _bound.getMidY();
	auto isTop = rect.getMinY() >= _bound.getMidY();
	//左边
	if (rect.getMinX() < _bound.getMidX() && rect.getMaxX() <= _bound.getMidX())
	{
		if (isBottom)
			return 2;
		if (isTop)
			return 1;
	}
	else if (rect.getMinX() >= _bound.getMidX())
	{
		if (isBottom)
			return 3;
		if (isTop)
			return 0;
	}

	return -1;
}

void QuadTree::clear()
{
	_root.clear();
	for (auto i = 0; i < 4; i++)
	{
		if (_child[i])
		{
			_child[i]->clear();
			_child[i] = nullptr;
		}
	}
}

QuadTree::QuadTree(int depth, cocos2d::Rect bound)
	:_depth(depth), _bound(bound)
{
	_child[0] = nullptr;
	_child[1] = nullptr;
	_child[2] = nullptr;
	_child[3] = nullptr;
	_root.clear();
}

QuadTree::~QuadTree()
{
	CC_SAFE_DELETE(_child[0]);
	CC_SAFE_DELETE(_child[1]);
	CC_SAFE_DELETE(_child[2]);
	CC_SAFE_DELETE(_child[3]);
}
