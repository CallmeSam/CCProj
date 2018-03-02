#pragma once
#ifndef __PARSER_H__
#define __PARSER_H__

#include "cocos2d.h"

//json
#include "json\rapidjson.h"
#include "json\document.h"
#include "json\prettywriter.h"
#include "json\stringbuffer.h"

class Parser
{
public:
	static void ParserXmlToValueVector(const std::string& path, cocos2d::ValueVector& valueVector);
	static void ParserXmlToValueMap(const std::string& path, cocos2d::ValueMap& valueVector);
	static void ParserJsonToValueVector(const std::string& path, cocos2d::ValueVector& valueVector);
	static void ParserJsonToValueMap(const std::string& path, cocos2d::ValueMap& valueVector);

	static void ParserJsonRecursive(rapidjson::Value& j_value, cocos2d::Value& value);
private:

};



#endif // !__PARSER_H__
