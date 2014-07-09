/*
 *             DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *    TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 *   0. You just DO WHAT THE FUCK YOU WANT TO.
 */

#include "UTF8.h"
#include "Unicode.h"

namespace
{
	#define Bits(a, i) (a >> (8-i))
	static const char B0      = 0;
	static const char B110    = 6;
	static const char B1110   = 14;
	static const char B11110  = 30;
	static const char B111110 = 62;
	
	const unsigned char toUC(const char c)
	{
		return *reinterpret_cast<const unsigned char*>(&c);
	}
	
	int GetMultibyteLength(const char c)
	{
		const unsigned char uc = toUC(c);
		int bytes = 1;
		     if(Bits(uc, 1) == B0     ) bytes = 1;
		else if(Bits(uc, 3) == B110   ) bytes = 2;
		else if(Bits(uc, 4) == B1110  ) bytes = 3;
		else if(Bits(uc, 5) == B11110 ) bytes = 4;
		else if(Bits(uc, 6) == B111110) bytes = 5;
		return bytes;
	}
	
	// We want: 00000000 00000001 01101000 01000100
	// First we need to ignore the bits used to declare the multibyte
	// We have: 11110000 10010110 10100001 10000100
	// Ignore:  ^^^^^    ^^       ^^       ^^
	// We can do that by 0'ing the first bits (Note: 0xff >> x = first x bits = 0, the rest = 1)
	// Octet 0: 11110000 & (0xff >> 5) = xxxx x000 
	// Octet 1: 10010110 & (0xff >> 2) = xx01 0110
	// Octet 2: 10100001 & (0xff >> 2) = xx10 0001
	// Octet 3: 10000100 & (0xff >> 2) = xx00 0100
	// Now we need to compose the 4 byte integer out of these, so we shift them into the right position and "or" them.
	// Octet 0: 11110000 << 6*3 = 000__ ________ ________
	// Octet 1: 10010110 << 6*2 = ___01 0110____ ________
	// Octet 2: 10100001 << 6*1 = _____ ____1000 01______
	// Octet 3: 10000100 <<   0 = _____ ________ __000100
	// Or them all:
	// We get:  00000000 00000001 01101000 01000100
	// We want: 00000000 00000001 01101000 01000100
	// Yay.
	Codepoint ComposeFromMultibyte(const char* c, int bytes)
	{
		const unsigned char* uc = reinterpret_cast<const unsigned char*>(c);
		Codepoint result = 0;
		result = ((*uc++) & (0xff >> (bytes+1))) << (bytes-1)*6;
		int i = 0;
		while(++i < bytes)
			result |= ((*uc++) & (0xff >> 2)) << (bytes-1-i)*6;
		return result;
	};
	
	Codepoint GetUtf8Codepoint(const char* c, int& bytes)
	{
		const unsigned char* uc = reinterpret_cast<const unsigned char*>(c);
		bytes = GetMultibyteLength(*c);
		// Look at the first byte to find length
		if((*uc) < 0x80) // ASCII / Length 1 Octet
			return (*uc);
		else if((*uc) < 0xC0) // Continuation byte? Something is wrong here, skip it, output "bad" character
			return 0xFFFD; // Unicode Replacement Character - Replace the "bad" character to be better able to debug all this
		else
			return ComposeFromMultibyte(c, bytes);
	}
}

Codepoint UTF8::DecodeNext(const std::string& str, int* position)
{
	if((*position) >= str.size())
		return 0;
	int bytes;
	bytes = GetMultibyteLength(str[*position]);
	(*position) += bytes;
	return GetUtf8Codepoint(&str[*position], bytes);
}

Codepoint UTF8::DecodeAt(const std::string& str, int position)
{
	if(position >= str.size())
		return 0;
	int bytes;
	bytes = GetMultibyteLength(str[position]);
	return GetUtf8Codepoint(&str[position], bytes);
}

Codepoint UTF8::DecodeReverse(const std::string& str, int* position)
{
	if((*position) <= 0)
		return 0;
	(*position)--;
	while(position > 0)
	{
		if(toUC(str[*position]) >= 0x80 && toUC(str[*position]) < 0xC0)
			(*position)--;
		else
			break;
	}
	int bytes;
	return GetUtf8Codepoint(&str[*position], bytes);
}

void UTF8::SkipForward(const std::string& str, int* position, int characters)
{
	if(characters < 0) return SkipBackward(str, position, -characters);
	while(characters--)
		(*position) += GetMultibyteLength(str[*position]);
}

void UTF8::SkipBackward(const std::string& str, int* position, int characters)
{
	if(characters < 0) return SkipForward(str, position, -characters);
	while(characters--)
	{
		(*position)--;
		while(toUC(str[*position]) >= 0x80 && toUC(str[*position]) < 0xC0)
			(*position)--;
	}
}

std::string UTF8::Strip(const std::string& str, Codepoint c)
{
	std::string temp = UTF8::StripLeft(str, c);
	return UTF8::StripRight(temp, c);
}

std::string UTF8::StripLeft(const std::string& str, Codepoint c)
{
	int i = 0;
	Codepoint cur = UTF8::DecodeAt(str, i);
	while(c == cur)
	{
		if(i >= str.size())
			break;
		cur = UTF8::DecodeNext(str, &i);
	}
	return str.substr(i, std::string::npos);
}

std::string UTF8::StripRight(const std::string& str, Codepoint c)
{
	int i = str.size()-1;
	Codepoint cur = UTF8::DecodeAt(str, i);
	while(c == cur)
	{
		if(i <= 0)
			break;
		cur = UTF8::DecodeReverse(str, &i);
	}
	return str.substr(0, i+1);
}

std::string UTF8::Chop(const std::string& str, int fromStart, int fromEnd)
{
	int start = 0;
	int end = str.size();
	
	UTF8::SkipForward(str, &start, fromStart);
	UTF8::SkipBackward(str, &end, fromEnd);
	
	return str.substr(start, end-start);
}

std::string UTF8::EncodeDebug(Codepoint c)
{
	return Encode(UCS::Substitute(c));
}

std::string UTF8::Encode(Codepoint c)
{
	std::string text;
	text.reserve(4);

	if (c <= 0x7F)
	{
		// Plain single-byte ASCII.
		text.push_back(c);
	}
	else if (c <= 0x7FF)
	{
		// Two bytes.
		text.push_back(0xC0 | (c >> 6));
		text.push_back(0x80 | ((c >> 0) & 0x3F));
	}
	else if (c <= 0xFFFF)
	{
		// Three bytes.
		text.push_back(0xE0 | (c >> 12));
		text.push_back(0x80 | ((c >> 6) & 0x3F));
		text.push_back(0x80 | ((c >> 0) & 0x3F));
	}
	else if (c <= 0x1FFFFF)
	{
		// Four bytes.
		text.push_back(0xF0 | (c >> 18));
		text.push_back(0x80 | ((c >> 12) & 0x3F));
		text.push_back(0x80 | ((c >> 6) & 0x3F));
		text.push_back(0x80 | ((c >> 0) & 0x3F));
	}
	else
	{
			// Invalid char; don't encode anything.
	}
	
	return text;
}

bool UTF8::Contains(const std::string& str, Codepoint c)
{
	int i = 0;
	Codepoint cur = UTF8::DecodeAt(str, i);
	while(cur = UTF8::DecodeNext(str, &i))
		if(cur == c) return true;
	return false;
}
