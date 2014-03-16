// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "StringParser.h"
#include <Springbok/Generic/LogicChain.h>

template<typename Condition>
std::string StringParser::advanceTo(const Condition& cond)
{
	int start = mCurPosition;
	Codepoint cur;
	cur = UTF8::DecodeAt(mStringToParse, start);
	int stop = start;
	while(stop < mStringToParse.size())
	{
		if(LogicCompare(cond, cur))
		{
			mCurPosition = stop;
			UTF8::SkipForward(mStringToParse, &mCurPosition, 1);
			return postProcess(mStringToParse.substr(start, stop-start));
		}
		cur = UTF8::DecodeNext(mStringToParse, &stop);
	}
	mCurPosition = stop;
	return postProcess(mStringToParse.substr(start, stop-start));
};