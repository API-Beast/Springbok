// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <string>
#include <vector>
#include "UTF8Decoder.h"

class StringParser
{
public:
	StringParser(const std::string& toParse, size_t start = 0);
	StringParser(const UTF8SubString& string);
	UTF8SubString advanceTo(std::vector<Codepoint> characters);
	UTF8SubString advanceTo(Codepoint character);
	Codepoint next();
	Codepoint cur();
	UTF8SubString getNested(Codepoint start, Codepoint stop);
	template<typename T>
	auto getNested(Codepoint start, Codepoint stop, T call) -> decltype(call(UTF8SubString(std::string(), 0, 0)))
	{
		return call(getNested(start, stop));
	};
	bool atEnd();
	std::string str();
public:
	bool StripWhitespace = true;
	bool SkipWhitespace = true;
	Codepoint SingleLineCommentCharacter = 0;
private:
	const std::string& mParent;
};
