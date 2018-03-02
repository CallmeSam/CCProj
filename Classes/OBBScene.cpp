#include "OBBScene.h"
USING_NS_CC;

bool OBBScene::init()
{
	if(!Scene::init())
		return false;

	_draw = DrawNode::create();
	addChild(_draw);

	_sp_1 = Sprite::create("tree2.png");
	addChild(_sp_1);
	auto action = Spawn::create(
		MoveBy::create(3.0f, Vec2(400, 0)),
		RotateBy::create(3.0f, 360),
		nullptr
	);
	_sp_1->setPosition(Vec2(100, 200));
	_sp_1->runAction(RepeatForever::create(Sequence::create(action, action->reverse(), nullptr)));

	_sp_2 = Sprite::create("tree2.png");
	_sp_2->setPosition(Vec2(200, 200));
	_sp_2->runAction(RepeatForever::create(RotateBy::create(3.0f, 360)));
	addChild(_sp_2);


	scheduleUpdate();

	return true;
}

void OBBScene::update(float dt)
{
	_draw->clear();

	OBB_2 obbA(_sp_1->getPosition(),  - _sp_1->getRotation(), _sp_1->getContentSize());
	OBB_2 obbB(_sp_2->getPosition(),  - _sp_2->getRotation(), _sp_2->getContentSize());

	_draw->drawLine(obbA._vertex[0], obbA._vertex[1], Color4F::RED);
	_draw->drawLine(obbA._vertex[1], obbA._vertex[3], Color4F::RED);
	_draw->drawLine(obbA._vertex[3], obbA._vertex[2], Color4F::RED);
	_draw->drawLine(obbA._vertex[2], obbA._vertex[0], Color4F::RED);
	
	_draw->drawLine(obbB._vertex[2], obbB._vertex[0], Color4F::GREEN);
	_draw->drawLine(obbB._vertex[0], obbB._vertex[1], Color4F::GREEN);
	_draw->drawLine(obbB._vertex[3], obbB._vertex[2], Color4F::GREEN);
	_draw->drawLine(obbB._vertex[1], obbB._vertex[3], Color4F::GREEN);

	if (obbA.isCollideWithOBB(obbB))
	{
		_sp_1->setColor(Color3B::RED);
		_sp_2->setColor(Color3B::RED);
	}
	else
	{
		_sp_1->setColor(Color3B::WHITE);
		_sp_2->setColor(Color3B::WHITE);
	}
	
}

OBB_2::OBB_2(const Vec2& center, float rotate,const cocos2d::Size& size)
{
	auto radius = CC_DEGREES_TO_RADIANS(rotate);
	auto origin = Vec2(center - size / 2);
	_vertex[0] = origin.rotateByAngle(center, radius);
	_vertex[1] = (origin + Vec2(size.width, 0)).rotateByAngle(center, radius);
	_vertex[2] = (origin + Vec2(0, size.height)).rotateByAngle(center, radius);
	_vertex[3] = (origin + size).rotateByAngle(center, radius);
}

Projection_2 OBB_2::getProject(const cocos2d::Vec2 & axis)
{
	auto normalize = axis.getNormalized();
	float max = _vertex[0].dot(normalize);
	float min = max;

	for (auto i = 1; i < 4; i++)
	{
		auto val = _vertex[i].dot(normalize);
		min = min < val ? min : val;
		max = max > val ? max : val;
	}
	return Projection_2(min, max);
}

//只需要判断两个轴即可
bool OBB_2::isCollideWithOBB(OBB_2 & obb)
{
	auto axisX = _vertex[1] - _vertex[0];
	if (!this->getProject(axisX).isOverlap(obb.getProject(axisX)))
		return false;
	auto axisY = _vertex[2] - _vertex[0];
	if (!this->getProject(axisY).isOverlap(obb.getProject(axisY)))
		return false;

	axisX = obb._vertex[1] - obb._vertex[0];
	if (!obb.getProject(axisX).isOverlap(this->getProject(axisX)))
		return false;

	axisY = obb._vertex[2] - obb._vertex[0];
	if (!obb.getProject(axisY).isOverlap(this->getProject(axisY)))
		return false;

	return true;
}


bool Projection_2::isOverlap(const Projection_2 & proj)
{
	assert(proj.axis == this->axis);

	if (this->_max < proj._min || proj._max < this->_min)
		return false;
	else
		return true;
}
