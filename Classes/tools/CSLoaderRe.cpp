#include "CSLoaderRe.h"

#include "base/ObjectFactory.h"
#include "base/CCDirector.h"
#include "base/ccUTF8.h"
#include "ui/CocosGUI.h"
#include "2d/CCSpriteFrameCache.h"
#include "2d/CCParticleSystemQuad.h"
#include "2d/CCTMXTiledMap.h"
#include "platform/CCFileUtils.h"

#include "tools/ActionTimelineCacheRe.h"
#include "editor-support/cocostudio/ActionTimeline/CCActionTimeline.h"
#include "editor-support/cocostudio/ActionTimeline/CCActionTimelineNode.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "editor-support/cocostudio/CSParseBinary_generated.h"

#include "editor-support/cocostudio/WidgetReader/NodeReaderProtocol.h"
#include "editor-support/cocostudio/WidgetReader/NodeReaderDefine.h"

#include "editor-support/cocostudio/WidgetReader/NodeReader/NodeReader.h"
#include "editor-support/cocostudio/WidgetReader/SingleNodeReader/SingleNodeReader.h"
#include "editor-support/cocostudio/WidgetReader/SpriteReader/SpriteReader.h"
#include "editor-support/cocostudio/WidgetReader/ParticleReader/ParticleReader.h"
#include "editor-support/cocostudio/WidgetReader/GameMapReader/GameMapReader.h"
#include "editor-support/cocostudio/WidgetReader/ProjectNodeReader/ProjectNodeReader.h"
#include "editor-support/cocostudio/WidgetReader/ComAudioReader/ComAudioReader.h"

#include "editor-support/cocostudio/WidgetReader/ButtonReader/ButtonReader.h"
#include "editor-support/cocostudio/WidgetReader/CheckBoxReader/CheckBoxReader.h"
#include "editor-support/cocostudio/WidgetReader/ImageViewReader/ImageViewReader.h"
#include "editor-support/cocostudio/WidgetReader/TextBMFontReader/TextBMFontReader.h"
#include "editor-support/cocostudio/WidgetReader/TextReader/TextReader.h"
#include "editor-support/cocostudio/WidgetReader/TextFieldReader/TextFieldReader.h"
#include "editor-support/cocostudio/WidgetReader/TextAtlasReader/TextAtlasReader.h"
#include "editor-support/cocostudio/WidgetReader/LoadingBarReader/LoadingBarReader.h"
#include "editor-support/cocostudio/WidgetReader/SliderReader/SliderReader.h"
#include "editor-support/cocostudio/WidgetReader/LayoutReader/LayoutReader.h"
#include "editor-support/cocostudio/WidgetReader/ScrollViewReader/ScrollViewReader.h"
#include "editor-support/cocostudio/WidgetReader/PageViewReader/PageViewReader.h"
#include "editor-support/cocostudio/WidgetReader/ListViewReader/ListViewReader.h"
#include "editor-support/cocostudio/WidgetReader/ArmatureNodeReader/ArmatureNodeReader.h"
#include "editor-support/cocostudio/WidgetReader/Node3DReader/Node3DReader.h"
#include "editor-support/cocostudio/WidgetReader/Sprite3DReader/Sprite3DReader.h"
#include "editor-support/cocostudio/WidgetReader/UserCameraReader/UserCameraReader.h"
#include "editor-support/cocostudio/WidgetReader/Particle3DReader/Particle3DReader.h"
#include "editor-support/cocostudio/WidgetReader/GameNode3DReader/GameNode3DReader.h"
#include "editor-support/cocostudio/WidgetReader/Light3DReader/Light3DReader.h"
#include "editor-support/cocostudio/WidgetReader/TabControlReader/TabControlReader.h"

#include "editor-support/cocostudio/WidgetReader/SkeletonReader/BoneNodeReader.h"
#include "editor-support/cocostudio/WidgetReader/SkeletonReader/SkeletonNodeReader.h"
#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/util.h"

#include "editor-support/cocostudio/FlatBuffersSerialize.h"

#include "editor-support/cocostudio/WidgetCallBackHandlerProtocol.h"

#include <fstream>

using namespace cocos2d::ui;
using namespace cocostudio;
using namespace cocostudio::timeline;
/* peterson */
using namespace flatbuffers;

USING_NS_CC;
static CSLoaderRe* _sharedCSLoaderRe = nullptr;

CSLoaderRe * CSLoaderRe::getInstance()
{
	if (!_sharedCSLoaderRe)
	{
		_sharedCSLoaderRe = new (std::nothrow) CSLoaderRe();
		_sharedCSLoaderRe->init();
	}

	return _sharedCSLoaderRe;
}

void CSLoaderRe::destroyInstance()
{
	
	CC_SAFE_DELETE(_sharedCSLoaderRe);
	cocostudio::timeline::ActionTimelineCache::destroyInstance();
}

cocos2d::Node * CSLoaderRe::createNode(const std::string & filename)
{
	std::string path = filename;
	size_t pos = path.find_last_of('.');
	std::string suffix = path.substr(pos + 1, path.length());

	CSLoaderRe* load = CSLoaderRe::getInstance();

	if (suffix == "csb")
	{
		return load->createNodeWithFlatBuffersFile(filename);
	}

	return nullptr;
}

cocos2d::Node * CSLoaderRe::createNode(const Data & data, const ccNodeLoadCallback & callback)
{
	CSLoaderRe * loader = CSLoaderRe::getInstance();
	Node * node = nullptr;
	do
	{
		CC_BREAK_IF(data.isNull() || data.getSize() <= 0);
		auto csparsebinary = GetCSParseBinary(data.getBytes());
		CC_BREAK_IF(nullptr == csparsebinary);
		auto csBuildId = csparsebinary->version();
		if (csBuildId)
		{
			CCASSERT(strcmp(loader->_csBuildID.c_str(), csBuildId->c_str()) == 0,
				StringUtils::format("%s%s%s%s%s%s%s%s%s%s",
					"The reader build id of your Cocos exported file(",
					csBuildId->c_str(),
					") and the reader build id in your Cocos2d-x(",
					loader->_csBuildID.c_str(),
					") are not match.\n",
					"Please get the correct reader(build id ",
					csBuildId->c_str(),
					")from ",
					"http://www.cocos2d-x.org/filedown/cocos-reader",
					" and replace it in your Cocos2d-x").c_str());
		}

		// decode plist
		auto textures = csparsebinary->textures();
		int textureSize = csparsebinary->textures()->size();
		CCLOG("textureSize = %d", textureSize);
		for (int i = 0; i < textureSize; ++i)
		{
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile(textures->Get(i)->c_str());
		}

		node = loader->nodeWithFlatBuffers(csparsebinary->nodeTree(), callback);
	} while (0);

	loader->reconstructNestNode(node);

	return node;
}

cocostudio::timeline::ActionTimeline * CSLoaderRe::createTimeline(const std::string & filename)
{
	std::string suffix = getExtentionName(filename);

	ActionTimelineCacheRe* cache = ActionTimelineCacheRe::getInstance();

	if (suffix == "csb")
	{
		return cache->createActionWithFlatBuffersFile(filename);
	}
	else if (suffix == "json" || suffix == "ExportJson")
	{
		return cache->createActionFromJson(filename);
	}

	return nullptr;
}

cocostudio::timeline::ActionTimeline * CSLoaderRe::createTimeline(const Data & data, const std::string & filename)
{
	std::string suffix = getExtentionName(filename);

	ActionTimelineCacheRe* cache = ActionTimelineCacheRe::getInstance();

	if (suffix == "csb")
	{
		return cache->createActionWithDataBuffer(data, filename);
	}
	else if (suffix == "json" || suffix == "ExportJson")
	{
		std::string content((char *)data.getBytes(), data.getSize());
		return cache->createActionFromContent(filename, content);
	}

	return nullptr;
}

cocos2d::Node * CSLoaderRe::nodeWithFlatBuffersFile(const std::string & fileName, const ccNodeLoadCallback & callback)
{
	std::string fullPath = FileUtils::getInstance()->fullPathForFilename(fileName);

	CC_ASSERT(FileUtils::getInstance()->isFileExist(fullPath));

	Data buf = FileUtils::getInstance()->getDataFromFile(fullPath);

	if (buf.isNull())
	{
		CCLOG("CSLoader::nodeWithFlatBuffersFile - failed read file: %s", fileName.c_str());
		CC_ASSERT(false);
		return nullptr;
	}

	auto csparsebinary = GetCSParseBinary(buf.getBytes());


	auto csBuildId = csparsebinary->version();
	if (csBuildId)
	{
		CCASSERT(strcmp(_csBuildID.c_str(), csBuildId->c_str()) == 0,
			StringUtils::format("%s%s%s%s%s%s%s%s%s%s",
				"The reader build id of your Cocos exported file(",
				csBuildId->c_str(),
				") and the reader build id in your Cocos2d-x(",
				_csBuildID.c_str(),
				") are not match.\n",
				"Please get the correct reader(build id ",
				csBuildId->c_str(),
				")from ",
				"http://www.cocos2d-x.org/filedown/cocos-reader",
				" and replace it in your Cocos2d-x").c_str());
	}

	// decode plist
	auto textures = csparsebinary->textures();
	int textureSize = textures->size();
	for (int i = 0; i < textureSize; ++i)
	{
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(textures->Get(i)->c_str());
	}

	Node* node = nodeWithFlatBuffers(csparsebinary->nodeTree(), callback);

	return node;
}

cocos2d::Node * CSLoaderRe::nodeWithFlatBuffers(const flatbuffers::NodeTree * nodetree, const ccNodeLoadCallback & callback)
{
	if (nodetree == nullptr)
		return nullptr;

	{
		Node* node = nullptr;

		std::string classname = nodetree->classname()->c_str();

		auto options = nodetree->options();

		if (classname == "ProjectNode")
		{
			auto reader = ProjectNodeReader::getInstance();
			auto projectNodeOptions = (ProjectNodeOptions*)options->data();
			std::string filePath = projectNodeOptions->fileName()->c_str();

			cocostudio::timeline::ActionTimeline* action = nullptr;
			if (filePath != "" && FileUtils::getInstance()->isFileExist(filePath))
			{
				Data buf = FileUtils::getInstance()->getDataFromFile(filePath);
				node = createNode(buf, callback);
				action = createTimeline(buf, filePath);
			}
			else
			{
				node = Node::create();
			}
			reader->setPropsWithFlatBuffers(node, (const flatbuffers::Table*)options->data());
			if (action)
			{
				action->setTimeSpeed(projectNodeOptions->innerActionSpeed());
				node->runAction(action);
				action->gotoFrameAndPause(0);
			}
		}
		else if (classname == "SimpleAudio")
		{
			node = Node::create();
			auto reader = ComAudioReader::getInstance();
			Component* component = reader->createComAudioWithFlatBuffers((const flatbuffers::Table*)options->data());
			if (component)
			{
				component->setName(PlayableFrame::PLAYABLE_EXTENTION);
				node->addComponent(component);
				reader->setPropsWithFlatBuffers(node, (const flatbuffers::Table*)options->data());
			}
		}
		else
		{
			std::string customClassName = nodetree->customClassName()->c_str();
			if (customClassName != "")
			{
				classname = customClassName;
			}
			std::string readername = getGUIClassName(classname);
			readername.append("Reader");

			NodeReaderProtocol* reader = dynamic_cast<NodeReaderProtocol*>(ObjectFactory::getInstance()->createObject(readername));
			if (reader)
			{
				node = reader->createNodeWithFlatBuffers((const flatbuffers::Table*)options->data());
			}

			Widget* widget = dynamic_cast<Widget*>(node);
			if (widget)
			{
				std::string callbackName = widget->getCallbackName();
				std::string callbackType = widget->getCallbackType();

				bindCallback(callbackName, callbackType, widget, _rootNode);
			}

			/* To reconstruct nest node as WidgetCallBackHandlerProtocol. */
			auto callbackHandler = dynamic_cast<WidgetCallBackHandlerProtocol *>(node);
			if (callbackHandler)
			{
				_callbackHandlers.pushBack(node);
				_rootNode = _callbackHandlers.back();
			}
			/**/
			//        _loadingNodeParentHierarchy.push_back(node);
		}

		// If node is invalid, there is no necessity to process children of node.
		if (!node)
		{
			return nullptr;
		}

		auto children = nodetree->children();
		int size = children->size();
		for (int i = 0; i < size; ++i)
		{
			auto subNodeTree = children->Get(i);
			Node* child = nodeWithFlatBuffers(subNodeTree, callback);
			if (child)
			{
				PageView* pageView = dynamic_cast<PageView*>(node);
				ListView* listView = dynamic_cast<ListView*>(node);
				if (pageView)
				{
					Layout* layout = dynamic_cast<Layout*>(child);
					if (layout)
					{
						pageView->addPage(layout);
					}
				}
				else if (listView)
				{
					Widget* widget = dynamic_cast<Widget*>(child);
					if (widget)
					{
						listView->pushBackCustomItem(widget);
					}
				}
				else
				{
					node->addChild(child);
				}

				if (callback)
				{
					callback(child);
				}
			}
		}

		//    _loadingNodeParentHierarchy.pop_back();

		return node;
	}
}
