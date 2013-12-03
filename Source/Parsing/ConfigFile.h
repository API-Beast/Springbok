// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "StringParser.h"
#include <vector>

class ConfigFile
{
public:
	struct PossibleArray
	{
		operator std::string&(){ if(Data.empty()) Data.push_back(""); return Data.back(); };
		operator std::vector<std::string>&(){ return Data; };
		operator std::string() const { if(Data.empty()) return ""; else return Data.back(); };
		operator const std::vector<std::string>&() const{ return Data; };
		PossibleArray& operator=(const std::vector<std::string>& other);
		PossibleArray& operator=(const std::string& other);
		bool operator==(const std::string& s);
		bool operator==(const std::vector<std::string>& v);
		PossibleArray(const std::string& s){ Data.push_back(s); };
		std::vector<std::string> Data;
	};
	struct KeyValue
	{
		KeyValue(const std::string& k, const PossibleArray& parray) : Key(k), Value(parray){};
		std::string Key;
		PossibleArray Value;
	};
	struct Object
	{
		Object() = default;
		Object(std::string name, Object* parent)
		{
			TypeHint = name;
			Parent = parent;
			Values.reserve(1);
			Children.reserve(1);
		};
		
		std::string TypeHint = "__undefined__";
		std::vector<KeyValue> Values;
		std::vector<Object> Children;
		Object* Parent = nullptr;
		
		PossibleArray& operator[](const std::string& key);
	};
public:
	ConfigFile();
	ConfigFile(const std::string& path);
	void loadFromBuffer(const std::string& content);
	void loadFromFile(const std::string& path);
	operator ConfigFile::Object&(){ return Root; };
	PossibleArray& operator[](const std::string& key){ return Root[key]; };
public:
	Object Root;
};
