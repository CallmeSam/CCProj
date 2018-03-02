#pragma once
#ifndef __ACTION_TIMELINE_CACHE_RE_H__
#define __ACTION_TIMELINE_CACHE_RE_H__

#include "editor-support/cocostudio/ActionTimeline/CCActionTimelineCache.h"

class ActionTimelineCacheRe : public cocostudio::timeline::ActionTimelineCache
{
public:
	/** Gets the singleton */
	static ActionTimelineCacheRe* getInstance();

	/** Destroys the singleton */
	static void destroyInstance();

	cocostudio::timeline::ActionTimeline* createActionWithDataBuffer(cocos2d::Data data, const std::string &fileName);
protected:
	inline cocostudio::timeline::ActionTimeline* createActionWithDataBuffer(const cocos2d::Data& data) ;
};


#endif // !__ACTION_TIMELINE_CACHE_RE_H__
