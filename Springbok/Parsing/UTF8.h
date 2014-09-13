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
	
	std::string Strip     (const std::string& str, Codepoint c);
	std::string StripLeft (const std::string& str, Codepoint c);
	std::string StripRight(const std::string& str, Codepoint c);
	
	template<typename C> std::string StripWhile(const std::string& str, const C& c);
	template<typename C> std::string StripLeftWhile(const std::string& str, const C& c);
	template<typename C> std::string StripRightWhile(const std::string& str, const C& c);
	
	std::string Chop(const std::string& str, int fromStart, int fromEnd);
	bool Contains(const std::string& str, Codepoint c);
}

#include "UTF8_Templates.hpp"