/*
 *             DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *    TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 *   0. You just DO WHAT THE FUCK YOU WANT TO.
 */

#include "UTF8Decoder.h"

UTF8Decoder::UTF8Decoder(const std::string& parent, size_t pos) : mParent(parent), CurPos(pos)
{
	// Skip incomplete characters
	while(mParent[CurPos] >= char(0x80) && mParent[CurPos] < char(0xC0)) CurPos++;
}

namespace
{
	#define Bits(a, i) (a >> (8-i))
	static const char B0      = 0;
	static const char B110    = 6;
	static const char B1110   = 14;
	static const char B11110  = 30;
	static const char B111110 = 62;
	
	struct UCharPtr
	{
		UCharPtr(const char* c){ Char = c; };
		operator const unsigned char*&()
		{
			return UChar;
		}
		union
		{
			const char* Char;
			const unsigned char* UChar;
		};
	};
	
	int GetMultibyteLength(const unsigned char c)
	{
		int bytes = 1;
		     if(Bits(c, 1) == B0     ) bytes = 1;
		else if(Bits(c, 3) == B110   ) bytes = 2;
		else if(Bits(c, 4) == B1110  ) bytes = 3;
		else if(Bits(c, 5) == B11110 ) bytes = 4;
		else if(Bits(c, 6) == B111110) bytes = 5;
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
	Codepoint ComposeFromMultibyte(const unsigned char* c, int bytes)
	{
		Codepoint result = 0;
		result = ((*c++) & (0xff >> (bytes+1))) << (bytes-1)*6;
		int i = 0;
		while(++i < bytes)
			result |= ((*c++) & (0xff >> 2)) << (bytes-1-i)*6;
		return result;
	};
	
	Codepoint GetUtf8Codepoint(const unsigned char* c, int& bytes)
	{
		bytes = GetMultibyteLength(*c);
		// Look at the first byte to find length
		if((*c) < 0x80) // ASCII / Length 1 Octet
			return (*c);
		else if((*c) < 0xC0) // Continuation byte? Something is wrong here, skip it, output "bad" character
			return 0xFFFD; // Unicode Replacement Character - Replace the "bad" character to be better able to debug all this
		else
			return ComposeFromMultibyte(c, bytes);
	}
}

const unsigned char& UTF8Decoder::curChar()
{
	return *reinterpret_cast<const unsigned char*>(&mParent[CurPos]);
}

UTF8Decoder& UTF8Decoder::operator++()
{
	int bytes;
	mCurrentCodepoint = GetUtf8Codepoint(&curChar(), bytes);
	CurPos += bytes;
	return *this;
}

UTF8Decoder& UTF8Decoder::operator--()
{
	CurPos--;
	// Advance to last actual start byte
	// FIXME If a string has loose continuation bytes operator-- doesn't reverse operator++
	while(curChar() >= 0x80 && curChar() < 0xC0) CurPos--;
	int bytes;
	mCurrentCodepoint = GetUtf8Codepoint(&curChar(), bytes);
	return *this;
}

UTF8Decoder& UTF8Decoder::operator+=(int i)
{
	if(i == 0) return *this;
	if(i  < 0) return operator-=(-i);
	while(i--)
		CurPos += GetMultibyteLength(curChar());
	int bytes;
	mCurrentCodepoint = GetUtf8Codepoint(&curChar(), bytes);
	return *this;
}

UTF8Decoder& UTF8Decoder::operator-=(int i)
{
	if(i == 0) return *this;
	if(i  < 0) return operator+=(-i);
	while(i--)
		CurPos -= GetMultibyteLength(curChar());
	int bytes;
	mCurrentCodepoint = GetUtf8Codepoint(&curChar(), bytes);
	return *this;
}

UTF8SubString::UTF8SubString(const std::string& parent, size_t pos, size_t end) : mParent(parent), Start(pos), End(end)
{

}

UTF8SubString UTF8SubString::strip(Codepoint c)
{
	UTF8SubString temp = lstrip(c);
	return temp.rstrip(c);
}

UTF8SubString UTF8SubString::lstrip(Codepoint c)
{
	UTF8Decoder it(mParent, Start);
	while(((it++) == c) && (it.CurPos < End));
	return UTF8SubString(mParent, it.CurPos, End);
}

UTF8SubString UTF8SubString::rstrip(Codepoint c)
{
	UTF8Decoder it(mParent, End);
	while(((it--) == c) && (it.CurPos < End));
	return UTF8SubString(mParent, Start, it.CurPos);
}

Codepoint UTF8SubString::operator[](int i)
{
	return UTF8Decoder(mParent, Start) += i;
}

Codepoint UTF8SubString::end(int i)
{
	return UTF8Decoder(mParent, End) -= i;
}

UTF8SubString::operator std::string() const
{
	return mParent.substr(Start, End);
}
