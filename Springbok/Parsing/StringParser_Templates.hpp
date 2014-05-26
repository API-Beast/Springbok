// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "StringParser.h"

template<typename C>
std::string StringParser::advanceTo(const C& cond, bool includeEnd)
{
	int start = mCurPosition;
	Codepoint cur;
	int stop = start;
	cur = UTF8::DecodeNext(mStringToParse, &stop);
	while(stop < mStringToParse.size())
	{
		if(cond(cur))
		{
			mCurPosition = stop;
			if(includeEnd) UTF8::SkipForward(mStringToParse, &mCurPosition, 1);
			return postProcess(mStringToParse.substr(start, mCurPosition-start));
		}
		cur = UTF8::DecodeNext(mStringToParse, &stop);
	}
	mCurPosition = stop;
	return postProcess(mStringToParse.substr(start, mCurPosition-start));
};