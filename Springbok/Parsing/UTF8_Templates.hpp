#pragma once

#include "UTF8.h"

template<typename C>
std::string UTF8::StripWhile(const std::string& str, const C& c)
{
	std::string temp = UTF8::StripLeftWhile(str, c);
	return UTF8::StripRightWhile(temp, c);
}

template<typename C>
std::string UTF8::StripLeftWhile(const std::string& str, const C& c)
{
	int i = 0;
	Codepoint cur = UTF8::DecodeAt(str, i);
	while(c(cur))
	{
		if(i >= str.size())
			break;
		cur = UTF8::DecodeNext(str, &i);
	}
	return str.substr(i, std::string::npos);
}

template<typename C>
std::string UTF8::StripRightWhile(const std::string& str, const C& c)
{
	int i = str.size()-1;
	Codepoint cur = UTF8::DecodeAt(str, i);
	while(c(cur))
	{
		if(i <= 0)
			break;
		cur = UTF8::DecodeReverse(str, &i);
	}
	return str.substr(0, i+1);
}
