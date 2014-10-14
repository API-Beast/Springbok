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
	
	std::string advanceTo(Codepoint point);
	
	template<typename C> std::string advanceTo(const C& cond);
	template<typename C> std::string advanceWhile(const C& cond);
	
	Codepoint next();
	Codepoint skipAhead();
	Codepoint peekAhead();
	Codepoint peek(int i = 0);
	Codepoint last();
	std::string advanceToNested(Codepoint start, Codepoint stop);
	bool atEnd();
	std::string str();
	void reset(int to=0);
	
	void skip(int i);
	void reroll(int);
public:
	bool StripWhitespace = true;
	bool SkipWhitespace = true;
	int  Position;
private:
	std::string mStringToParse;
	std::string postProcess(const std::string& s);
};

#include "StringParser_Templates.hpp"