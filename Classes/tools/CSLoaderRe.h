#pragma once
#ifndef __CS_LOADER_RE_H__
#define __CS_LOADER_RE_H__
#include "editor-support/cocostudio/ActionTimeline/CSLoader.h"

USING_NS_CC;

class CSLoaderRe : public cocos2d::CSLoader
{
public :
	static CSLoaderRe* getInstance();
	static void destroyInstance();

	static cocos2d::Node* createNode(const std::string& filename);
	static cocos2d::Node* createNode(const cocos2d::Data& data, const ccNodeLoadCallback &callback);
	static cocostudio::timeline::ActionTimeline* createTimeline(const std::string& filename);
	static cocostudio::timeline::ActionTimeline* createTimeline(const cocos2d::Data& data, const std::string& filename);

protected:
	cocos2d::Node* nodeWithFlatBuffersFile(const std::string& fileName, const ccNodeLoadCallback& callback);
	cocos2d::Node* nodeWithFlatBuffers(const flatbuffers::NodeTree* nodetree, const ccNodeLoadCallback& callback);

};




#endif // !__CS_LOADER_RE_H__
