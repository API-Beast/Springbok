// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#include "ConfigFile.h"
#include <fstream>
#include <stack>

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
				(*shallowContext)[key] = vector<string>(1, p.getNested('"', '"'));
			// Arrays
			else if(p.cur() == '[')
				(*shallowContext)[key] = parseArray(p.getNested('[', ']'));
			// Implicit strings
			else
				(*shallowContext)[key] = vector<string>(1, p.advanceTo('\n'));
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

ConfigFile::ConfigFile(const string& path)
{
	ifstream file(path, ios::binary);
	streambuf* fileBuffer = file.rdbuf();
	string fileContent;
	auto size = fileBuffer->pubseekoff(0, ios_base::end);
	fileContent.reserve(size);
	fileBuffer->sgetn(&fileContent[0], size);
	parseObject(fileContent, Root);

}