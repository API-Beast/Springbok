/*
 *             DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *    TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 *   0. You just DO WHAT THE FUCK YOU WANT TO.
 */

#pragma once

#include <string>
#include <cinttypes>

typedef unsigned char Byte;
typedef char32_t Codepoint;

class UTF8Decoder
{
public:
	UTF8Decoder(const std::string& parent, size_t pos=0);
	UTF8Decoder& operator++();
	UTF8Decoder& operator--();
	UTF8Decoder& operator++(int){ return this->operator++(); };
	UTF8Decoder& operator--(int){ return this->operator--(); };
	UTF8Decoder& operator+=(int i);
	UTF8Decoder& operator-=(int i);
	bool operator==(const UTF8Decoder& other) const{ return other.CurPos == CurPos; };
	operator Codepoint() const{ return mCurrentCodepoint; };
	//operator string() const;
	bool inRange() const { return CurPos < mParent.size(); }; // CurPos can't be below 0 since it is unsigned, so we don't need to check it
	size_t CurPos;
private:
	const unsigned char& curChar();
	const std::string& mParent;
	Codepoint mCurrentCodepoint = 0;
};

class UTF8SubString
{
public:
	UTF8SubString(const std::string& parent, size_t pos=0, size_t end=std::string::npos);
	Codepoint operator[](int i);
	Codepoint end(int i=0);
	UTF8SubString strip(Codepoint c);
	UTF8SubString rstrip(Codepoint c);
	UTF8SubString lstrip(Codepoint c);
	operator std::string() const;
	std::string toString() const{ return *this; };
public:
	size_t Start;
	size_t End;
private:
	const std::string& mParent;
};