// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#include "ConfigFile.h"
#include <fstream>
#include <stack>
#include <algorithm>
#include <Springbok/Generic/LogicChain.h>

using namespace std;

namespace
{
	void parseObject(const std::string& content, ConfigFile::Object* parent)
	{
		StringParser p(content);
		ConfigFile::Object* context = parent;
		ConfigFile::Object* shallowContext = parent;
		p.StripWhitespace = true;
		p.SkipWhitespace  = true;
		p.SingleLineCommentCharacter = ';';
		while(!p.atEnd())
		{
			std::string key = p.advanceTo(_or(_or(eq('='),eq('{')), eq('[')));
			Codepoint oper = p.last();
			// Assignment
			if(oper == '=')
			{
				auto parseArray = [](StringParser p)
				{
					vector<string> result;
					while(!p.atEnd())
					{
						auto curItem = p.advanceTo(',');
						result.push_back(UTF8::Strip(curItem, '"'));
					};
					return result;
				};
				// Explicit strings
				if(p.peek(+1) == '"')
					(*shallowContext)[key] = p.advanceTo('"');
				// Arrays
				else if(p.peek(+1) == '[')
					(*shallowContext)[key] = parseArray(p.advanceToNested('[', ']'));
				// Implicit strings
				else
					(*shallowContext)[key] = p.advanceTo('\n');
			}
			// Shallow Child Object
			else if(oper == '[')
			{
				context->Children.emplace_back(p.advanceTo(']'), context);
				shallowContext = &(context->Children.back());
			}
			// Hierachies
			else if(oper == '{')
			{
				context->Children.emplace_back(key, context);
				parseObject(p.advanceToNested('{', '}'), &(context->Children.back()));
			}
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
		if(p.last() != '.')
		{
			auto keyEqualTo = [&value](ConfigFile::KeyValue& obj){ return obj.Key == value; };
			auto it = std::find_if(context->Values.begin(), context->Values.end(), keyEqualTo);
			if(it == context->Values.end())
			{
				context->Values.emplace_back(value, ConfigFile::PossibleArray{""});
				return context->Values.back().Value;
			}
			return it->Value;
		}
		else
		{
			auto hintEqualTo = [&value](ConfigFile::Object& obj){ return obj.TypeHint == value; };
			ConfigFile::Object* oldContext = context;
			auto it = std::find_if(context->Children.begin(), context->Children.end(), hintEqualTo);
			if(it == context->Children.end())
			{
				oldContext->Children.emplace_back();
				oldContext->Children.back().TypeHint = value;
				context = &(oldContext->Children.back());
			}
			else
				context = &(*it);
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
	parseObject(content, &Root);
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

