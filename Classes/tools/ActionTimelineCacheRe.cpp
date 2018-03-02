#include "ActionTimelineCacheRe.h"
#include "editor-support/cocostudio/ActionTimeline/CSLoader.h"
#include "editor-support/cocostudio/ActionTimeline/CCFrame.h"
#include "editor-support/cocostudio/ActionTimeline/CCTimeLine.h"
#include "editor-support/cocostudio/ActionTimeline/CCActionTimeline.h"
#include "platform/CCFileUtils.h"
#include "2d/CCSpriteFrameCache.h"
#include "2d/CCSpriteFrame.h"

#include "editor-support/cocostudio/CSParseBinary_generated.h"

#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/util.h"

#include "editor-support/cocostudio/FlatBuffersSerialize.h"

#include <fstream>

using namespace cocos2d;
using namespace flatbuffers;

static ActionTimelineCacheRe* _sharedActionCache = nullptr;

ActionTimelineCacheRe * ActionTimelineCacheRe::getInstance()
{
	if (!_sharedActionCache)
	{
		_sharedActionCache = new (std::nothrow) ActionTimelineCacheRe();
		_sharedActionCache->init();
	}

	return _sharedActionCache;
}

void ActionTimelineCacheRe::destroyInstance()
{
	CC_SAFE_DELETE(_sharedActionCache);
}

cocostudio::timeline::ActionTimeline * ActionTimelineCacheRe::createActionWithDataBuffer(cocos2d::Data data, const std::string & fileName)
{
	return ActionTimelineCache::createActionWithDataBuffer(data, fileName);
}

inline cocostudio::timeline::ActionTimeline * ActionTimelineCacheRe::createActionWithDataBuffer(const cocos2d::Data & data)
{
	auto csparsebinary = GetCSParseBinary(data.getBytes());

	auto nodeAction = csparsebinary->action();
	auto action = cocostudio::timeline::ActionTimeline::create();

	int duration = nodeAction->duration();
	action->setDuration(duration);
	float speed = nodeAction->speed();
	action->setTimeSpeed(speed);

	auto animationlist = csparsebinary->animationList();
	int animationcount = animationlist->size();
	for (int i = 0; i < animationcount; i++)
	{
		auto animationdata = animationlist->Get(i);
		cocostudio::timeline::AnimationInfo info;
		info.name = animationdata->name()->c_str();
		info.startIndex = animationdata->startIndex();
		info.endIndex = animationdata->endIndex();
		action->addAnimationInfo(info);
	}

	auto timeLines = nodeAction->timeLines();
	int timelineLength = timeLines->size();
	std::multimap<std::string, cocostudio::timeline::Timeline*> properTimelineMap;// order the timelines depends property name
	for (int i = 0; i < timelineLength; i++)
	{
		auto timelineFlatBuf = timeLines->Get(i);
		cocostudio::timeline::Timeline* timeline = loadTimelineWithFlatBuffers(timelineFlatBuf);
		if (timeline)
		{
			properTimelineMap.emplace(timelineFlatBuf->property()->c_str(), timeline);
		}
	}

	for (const auto& properTimelinePair : properTimelineMap)
	{
		action->addTimeline(properTimelinePair.second);
	}
	return action;
}
