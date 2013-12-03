/*
 *             DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *    TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 *   0. You just DO WHAT THE FUCK YOU WANT TO.
 */

#pragma onced

#include <string>
#include <cinttypes>

typedef unsigned char Byte;
typedef char32_t Codepoint;

namespace UTF8
{
	Codepoint DecodeNext   (const std::string& str, int* position);
	Codepoint DecodeReverse(const std::string& str, int* position);
	Codepoint DecodeAt     (const std::string& str, int  position);
	
	std::string Encode(Codepoint c);
	std::string EncodeDebug(Codepoint c);
	
	void SkipForward (const std::string& str, int* position, int characters);
	void SkipBackward(const std::string& str, int* position, int characters);
	
	template<typename Condition> std::string Strip     (const std::string& str, const Condition& c);
	template<typename Condition> std::string StripLeft (const std::string& str, const Condition& c);
	template<typename Condition> std::string StripRight(const std::string& str, const Condition& c);
	
	std::string Chop(const std::string& str, int fromStart, int fromEnd);
}

#include "UTF8_Templates.hpp"