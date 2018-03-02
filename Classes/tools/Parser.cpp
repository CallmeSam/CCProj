#include "Parser.h"
//#include "unpackPraser\GetAssets.h"

//对应的类型是<array></array>
//并非是<plist version="1.0" name="tom">
void Parser::ParserXmlToValueVector(const std::string & path, cocos2d::ValueVector & valueVector)
{
	valueVector = cocos2d::FileUtils::getInstance()->getValueVectorFromFile(path.c_str());
}

void Parser::ParserXmlToValueMap(const std::string & path, cocos2d::ValueMap & valueMap)
{
	valueMap = cocos2d::FileUtils::getInstance()->getValueMapFromFile(path.c_str());
}

void Parser::ParserJsonToValueVector(const std::string & path, cocos2d::ValueVector & valueVector)
{
#if UNPACK_START
	auto data = GetAssets::getInstance()->getData(path.c_str());
	std::string text((const char*)data.getBytes());
#else
	std::string text = cocos2d::FileUtils::getInstance()->getStringFromFile(path.c_str());
#endif

	rapidjson::Document doc;
	doc.Parse<0>(text.c_str());
	CCASSERT(doc.IsArray(), "doc is not a array");
	for(int i = 0; i < doc.Capacity(); i++)
	{
		cocos2d::Value val;
		ParserJsonRecursive(doc[i], val);
		valueVector.push_back(val);
	}
}

void Parser::ParserJsonToValueMap(const std::string & path, cocos2d::ValueMap & valueVector)
{
	std::string text = cocos2d::FileUtils::getInstance()->getStringFromFile(path.c_str());
	rapidjson::Document doc;
	doc.Parse<0>(text.c_str());
	CCASSERT(doc.IsObject(), "doc is not a object");
	for (auto begin = doc.MemberBegin(); begin != doc.MemberEnd(); begin++)
	{
		cocos2d::Value val;
		ParserJsonRecursive(begin->value, val);
		valueVector[begin->name.GetString()] = val;
	}
}

void Parser::ParserJsonRecursive(rapidjson::Value & j_value, cocos2d::Value& value)
{
	if (j_value.IsDouble())
		value = cocos2d::Value(j_value.GetDouble());
	else if (j_value.IsInt())
		value = cocos2d::Value(j_value.GetInt());
	else if (j_value.IsString())
		value = cocos2d::Value(j_value.GetString());
	else if (j_value.IsBool())
		value = cocos2d::Value(j_value.GetBool());
	else if (j_value.IsArray())
	{
		value = cocos2d::Value(cocos2d::ValueVector());
		for (int i = 0; i < j_value.Capacity(); i++)
		{
			cocos2d::Value val;
			ParserJsonRecursive(j_value[i], val);
			value.asValueVector().push_back(val);
		}
	}
	else if (j_value.IsObject())
	{
		value = cocos2d::Value(cocos2d::ValueMap());
		for (auto begin = j_value.MemberBegin(); begin != j_value.MemberEnd(); begin++)
		{
			cocos2d::Value val;
			ParserJsonRecursive(begin->value, val);
			value.asValueMap()[begin->name.GetString()] = val;
		}
	}
	else
	{
		assert(false);
	}
}