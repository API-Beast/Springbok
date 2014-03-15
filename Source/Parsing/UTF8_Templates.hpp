#pragma once

#include "UTF8.h"
#include <Springbok/Generic/LogicChain.h>

template<typename Condition>
std::string UTF8::Strip(const std::string& str, const Condition& c)
{
	std::string temp = UTF8::StripLeft(str, c);
	return UTF8::StripRight(temp, c);
}

template<typename Condition>
std::string UTF8::StripLeft(const std::string& str, const Condition& c)
{
	int i = 0;
	Codepoint cur = UTF8::DecodeAt(str, i);
	while(LogicCompare(c, cur))
	{
		if(i >= str.size())
			break;
		cur = UTF8::DecodeNext(str, &i);
	}
	return str.substr(i, std::string::npos);
}

template<typename Condition>
std::string UTF8::StripRight(const std::string& str, const Condition& c)
{
	int i = str.size()-1;
	Codepoint cur = UTF8::DecodeAt(str, i);
	while(LogicCompare(c, cur))
	{
		if(i <= 0)
			break;
		cur = UTF8::DecodeReverse(str, &i);
	}
	return str.substr(0, i+1);
}
