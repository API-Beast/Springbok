// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <string>
#include <vector>
#include "UTF8.h"

class StringParser
{
public:
	StringParser(const std::string& toParse, int start = 0);
	std::string advanceTo(Codepoint point, bool includeEnd=false);
	template<typename C>
	std::string advanceTo(const C& cond, bool includeEnd=false);
	Codepoint next();
	Codepoint skipAhead();
	Codepoint peekAhead();
	Codepoint peek(int i = 0);
	Codepoint last();
	std::string advanceToNested(Codepoint start, Codepoint stop);
	bool atEnd();
	std::string str();
	void reset(int to=0);
public:
	bool StripWhitespace = true;
	bool SkipWhitespace = true;
private:
	std::string mStringToParse;
	int mCurPosition;
	std::string postProcess(const std::string& s);
};

#include "StringParser_Templates.hpp"