// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#include "StringParser.h"
#include "Unicode.h"

bool StringParser::atEnd()
{
	return !(mCurPosition < mStringToParse.size());
}

std::string StringParser::advanceToNested(Codepoint open, Codepoint close)
{
	int start = mCurPosition;
	int stop = mCurPosition;
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
	mCurPosition = stop;
	UTF8::SkipForward(mStringToParse, &mCurPosition, 1);
	return postProcess(mStringToParse.substr(start, stop-start));
}

Codepoint StringParser::peek(int i)
{
	int temp = mCurPosition;
	UTF8::SkipForward(mStringToParse, &temp, i);
	return UTF8::DecodeAt(mStringToParse, temp);
}

Codepoint StringParser::skipAhead()
{
	Codepoint cur = UTF8::DecodeAt(mStringToParse, mCurPosition);
	if(SkipWhitespace)
		while(UCS::IsWhitespace(cur))
			cur = UTF8::DecodeNext(mStringToParse, &mCurPosition);
	return mCurPosition;
}

Codepoint StringParser::peekAhead()
{
	int temp = mCurPosition;
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
	mCurPosition = to;
}

Codepoint StringParser::next()
{
	Codepoint cur = UTF8::DecodeAt(mStringToParse, mCurPosition);
	if(SkipWhitespace)
		while(UCS::IsWhitespace(cur))
			cur = UTF8::DecodeNext(mStringToParse, &mCurPosition);
	return UTF8::DecodeNext(mStringToParse, &mCurPosition);
}

std::string StringParser::str()
{
	return mStringToParse;
}

StringParser::StringParser(const std::string& toParse, int start) : mStringToParse(toParse), mCurPosition(start)
{

}

std::string StringParser::postProcess(const std::string& s)
{
	if(StripWhitespace)
		return UTF8::Strip(s,_or(&UCS::IsWhitespace, &UCS::IsInvisible));
}
