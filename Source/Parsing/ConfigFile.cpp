// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#include "ConfigFile.h"
#include <fstream>
#include <stack>
#include <algorithm>

using namespace std;

namespace
{
	void parseObject(const std::string& content, ConfigFile::Object& parent)
	{
		StringParser p(content);
		ConfigFile::Object* context = &parent;
		ConfigFile::Object* shallowContext = &parent;
		p.StripWhitespace = true;
		p.SkipWhitespace  = true;
		p.SingleLineCommentCharacter = ';';
		UTF8SubString key = p.advanceTo({'=', '{', '['});
		// Assignment
		if(p.cur() == '=')
		{
			auto parseArray = [](StringParser p)
			{
				vector<string> result;
				while(!p.atEnd())
				{
					auto curItem = p.advanceTo(',');
					result.push_back(curItem.strip('"'));
				};
				return result;
			};
			// Explicit strings
			if(p.next() == '"')
				(*shallowContext)[key] = p.getNested('"', '"');
			// Arrays
			else if(p.cur() == '[')
				(*shallowContext)[key] = parseArray(p.getNested('[', ']'));
			// Implicit strings
			else
				(*shallowContext)[key] = p.advanceTo('\n');
		}
		// Shallow Child Object
		if(p.cur() == '[')
		{
			ConfigFile::Object newObject;
			newObject.TypeHint = p.advanceTo(']');
			newObject.Parent = context;
			context->Children.push_back(newObject);
			shallowContext = &(context->Children.back());
		}
		// Hierachies
		if(p.cur() == '{')
		{
			ConfigFile::Object newObject;
			newObject.TypeHint = key;
			newObject.Parent = context;
			context->Children.push_back(newObject);
			parseObject(p.getNested('{', '}'), context->Children.back());
		}
	}
}

ConfigFile::PossibleArray& ConfigFile::Object::operator[](const string& key)
{
	StringParser p(key);
	ConfigFile::Object* context = this;
	while(true)
	{
		std::string value = p.advanceTo('.');
		if(p.cur() != '.')
		{
			auto keyEqualTo = [&value](ConfigFile::KeyValue& obj){ return obj.Key == value; };
			return std::find_if(context->Values.begin(), context->Values.end(), keyEqualTo)->Value;
		}
		else
		{
			auto hintEqualTo = [&value](ConfigFile::Object& obj){ return obj.TypeHint == value; };
			context = &(*std::find_if(context->Children.begin(), context->Children.end(), hintEqualTo));
		}
	}
}

ConfigFile::ConfigFile(const string& path)
{
	loadFromFile(path);
}

ConfigFile::ConfigFile(){}

void ConfigFile::loadFromFile(const string& path)
{
	ifstream file(path, ios::binary);
	streambuf* fileBuffer = file.rdbuf();
	string fileContent;
	auto size = fileBuffer->pubseekoff(0, ios_base::end);
	fileContent.reserve(size);
	fileBuffer->sgetn(&fileContent[0], size);
	loadFromBuffer(fileContent);
}

void ConfigFile::loadFromBuffer(const string& content)
{
	parseObject(content, Root);
}
bool ConfigFile::PossibleArray::operator==(const vector< string >& v)
{
	return Data == v;
}
bool ConfigFile::PossibleArray::operator==(const string& s)
{
	if(Data.size() == 1)
		return Data.back() == s;
	return false;
}
ConfigFile::PossibleArray& ConfigFile::PossibleArray::operator=(const string& other)
{
	Data = std::vector<std::string>(1, other);
	return *this;
}
ConfigFile::PossibleArray& ConfigFile::PossibleArray::operator=(const vector< string >& other)
{
	Data = other;
	return *this;
}

