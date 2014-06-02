//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "Vec4.h"

using Color = Vec3F;

constexpr Color RGB(float red, float green, float blue)
{
	return Color( red  ,
								green,
							  blue );
};

constexpr Color HTMLColor(unsigned int hex)
{
	return Color( ( (hex >> (8*2)) & 0xff ) / 255.f, 
							  ( (hex >> (8*1)) & 0xff ) / 255.f,
							  ( (hex >> (8*0)) & 0xff ) / 255.f);
};

namespace Colors
{
	static constexpr Color White = Color(1.0f);
	static constexpr Color Black = Color(0.0f);
	
#define _(NAME, CODE) static constexpr Color NAME = HTMLColor(CODE)
#define ___(NAME, CODEA, CODEB, CODEC) static constexpr Color NAME[] = {HTMLColor(CODEA), HTMLColor(CODEB), HTMLColor(CODEC)}

	// Based on Dawnbringers 32 Color palette.
	// Good for dark on bright background.
	// Muted, Not Gritty
	namespace Dawn
	{
		___(Silver,    0x595652, 0x848e93, 0xb7c4df);
		___(Copper,    0x663931, 0x8F563B, 0xD9A066);
		___(Charcoal,  0x11101B, 0x2a2841, 0x6a687c);
		___(Turquoise, 0x162635, 0x306e82, 0x37BA95);
		
		___(Red,       0xAC3232, 0xF2724A, 0xFFA22F);
		___(Yellow,    0x8A6f30, 0xB4C140, 0xFBF236);
		___(Green,     0x395024, 0x3CA14F, 0x99E550);
		___(Blue,      0x3F3F74, 0x5B6EE1, 0x5FCDE4);
		___(Purple,    0x45283C, 0x76428A, 0xD77BBA);
	}
	
	// TODO
	// Spaaace!
	// Good for bright on dark background. (e.g. Spaaaace!)
	/*namespace Neon
	{
		
	};*/
#undef _
#undef ___
};