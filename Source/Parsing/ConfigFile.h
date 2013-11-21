// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "StringParser.h"
#include <vector>

class ConfigFile
{
public:
	struct KeyValue
	{
		std::string Key;
		std::vector<std::string> Value;
	};
	struct Object
	{
		std::string TypeHint = "__undefined__";
		std::vector<KeyValue> Values;
		std::vector<Object> Children;
		Object* Parent = nullptr;
		
		std::vector<std::string>& operator[](const std::string& key);
	};
public:
	ConfigFile(const std::string& path);
	operator ConfigFile::Object&(){ return Root; };
public:
	Object Root;
};
