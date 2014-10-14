// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "StringParser.h"

template<typename C>
std::string StringParser::advanceTo(const C& cond)
{
	int start = Position;
	Codepoint cur;
	int stop = start;
	cur = UTF8::DecodeAt(mStringToParse, stop);
	while(stop < mStringToParse.size())
	{
		if(cond(cur))
		{
			Position = stop;
			std::string retVal = mStringToParse.substr(start, Position-start);
			UTF8::SkipForward(mStringToParse, &Position, 1);
			return postProcess(retVal);
		}
		cur = UTF8::DecodeNext(mStringToParse, &stop);
	}
	Position = stop;
	return postProcess(mStringToParse.substr(start, Position-start));
};

template<typename C>
std::string StringParser::advanceWhile(const C& cond)
{
	int start = Position;
	Codepoint cur;
	int stop = start;
	cur = UTF8::DecodeAt(mStringToParse, stop);
	while(stop < mStringToParse.size())
	{
		if(!cond(cur))
		{
			Position = stop;
			std::string retVal = mStringToParse.substr(start, Position-start);
			// Note that we don't skip forward here
			return postProcess(retVal);
		}
		cur = UTF8::DecodeNext(mStringToParse, &stop);
	}
	Position = stop;
	return postProcess(mStringToParse.substr(start, Position-start));
};