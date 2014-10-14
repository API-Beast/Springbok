// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#include "StringParser.h"
#include "Unicode.h"

bool StringParser::atEnd()
{
	return !(Position < mStringToParse.size());
}

std::string StringParser::advanceToNested(Codepoint open, Codepoint close)
{
	int start = Position;
	int stop = Position;
	int currentNesting = 1;
	Codepoint cur = UTF8::DecodeAt(mStringToParse, stop);
	while(stop < mStringToParse.size())
	{
		if(cur == open)
			currentNesting++;
		else if(cur == close)
			currentNesting--;
		if(!currentNesting)
			break;
		cur = UTF8::DecodeNext(mStringToParse, &stop);
	}
	Position = stop;
	UTF8::SkipForward(mStringToParse, &Position, 1);
	return postProcess(mStringToParse.substr(start, stop-start));
}

Codepoint StringParser::peek(int i)
{
	int temp = Position;
	UTF8::SkipForward(mStringToParse, &temp, i);
	return UTF8::DecodeAt(mStringToParse, temp);
}

Codepoint StringParser::skipAhead()
{
	Codepoint cur = UTF8::DecodeAt(mStringToParse, Position);
	if(SkipWhitespace)
		while(UCS::IsWhitespace(cur))
			cur = UTF8::DecodeNext(mStringToParse, &Position);
	return Position;
}

Codepoint StringParser::peekAhead()
{
	int temp = Position;
	Codepoint cur = UTF8::DecodeAt(mStringToParse, temp);
	if(SkipWhitespace)
		while(UCS::IsWhitespace(cur))
			cur = UTF8::DecodeNext(mStringToParse, &temp);
	return UTF8::DecodeNext(mStringToParse, &temp);
}

Codepoint StringParser::last()
{
	return peek(-1);
}

void StringParser::reset(int to)
{
	Position = to;
}

std::string StringParser::advanceTo(Codepoint point)
{
	int start = Position;
	Codepoint cur;
	int stop = start;
	cur = UTF8::DecodeAt(mStringToParse, stop);
	while(stop < mStringToParse.size())
	{
		if(cur == point)
		{
			Position = stop;
			std::string result = mStringToParse.substr(start, Position-start);
			UTF8::SkipForward(mStringToParse, &Position, 1);
			return postProcess(result);
		}
		cur = UTF8::DecodeNext(mStringToParse, &stop);
	}
	Position = stop;
	return postProcess(mStringToParse.substr(start, Position-start));
}

Codepoint StringParser::next()
{
	Codepoint cur = UTF8::DecodeAt(mStringToParse, Position);
	if(SkipWhitespace)
		while(UCS::IsWhitespace(cur))
			cur = UTF8::DecodeNext(mStringToParse, &Position);
	return UTF8::DecodeNext(mStringToParse, &Position);
}

std::string StringParser::str()
{
	return mStringToParse;
}

StringParser::StringParser(const std::string& toParse, int start) : mStringToParse(toParse), Position(start)
{

}

std::string StringParser::postProcess(const std::string& s)
{
	if(StripWhitespace)
		return UTF8::StripWhile(s, [](Codepoint c){ return UCS::IsWhitespace(c) || UCS::IsInvisible(c); });
	return s;
}

void StringParser::reroll(int i)
{
	UTF8::SkipBackward(mStringToParse, &Position, i);
}

void StringParser::skip(int i)
{
	UTF8::SkipForward(mStringToParse, &Position, i);
}
