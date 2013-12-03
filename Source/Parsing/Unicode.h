// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

namespace UCS
{

inline bool IsWhitespace(char32_t c)
{
	return c == ' ' || c == '\t'   || c == '\n'   || c == '\r'
									|| c == 0x00A0 || c == 0x1680 || c == 0x2028
									|| c == 0x2029 || c == 0x202F || c == 0x205F
									|| c == 0x3000 ;
}

inline bool IsInvisible(char32_t c)
{
	return c < 0x1f ||  c == 127 
	                || (c > 0x200E && c < 0x200F)
									|| (c > 0x202A && c < 0x202E)
									|| (c > 0x200C && c < 0x200D);
}

inline char32_t Substitute(char32_t c)
{
	if(c < 0x1F)
	{
		return 0x2400 + c;
	}
	switch(c)
	{
		case '\n':
			return 0x2424; // "Symbol for newline"
		case ' ':
			return 0x2420;
	}
	return c;
}

}