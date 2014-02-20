// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <Springbok/Geometry/Vec3.h>

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

Color HSY(float hue, float saturation, float luma);

namespace Colors
{
	static constexpr Color White = Color(1.0f);
	static constexpr Color Black = Color(0.0f);
	
#define _(NAME, CODE) static constexpr Color NAME = HTMLColor(CODE)
	// Palette from the KDE default icon theme. Good general purpose palette.
	namespace Oxygen
	{
		_(Brown,     0x866327); _(Red,   0xE70F00);
		_(Magenta,   0xE70082); _(Lilac, 0xAD3696);
		_(BlueLilac, 0x583796); _(Blue,  0x0069BA);
		_(Cyan,      0x008990); _(SeaGreen, 0x00A778);
		_(Green,     0x48B13C); _(Yellow,   0xFFE300);
		_(Orange,    0xEF8441);
		_(Black,     0x3E4547); _(Grey,     0x989A95); _(White,     0xF1F1EF);
	};
	
	// 100% Saturated colors; might not be the most appealing ones, visually.
	namespace Saturated
	{
		_(Red,    0xFF0000); _(Green,     0x00FF00); _(Blue,       0x0000FF);
		_(Yellow, 0xFFFF00); _(Orange,    0xFF8000); _(Lime,       0x80FF00);
		_(Cyan,   0x00FFFF); _(Turquoise, 0x00FF80); _(Aquamarine, 0x0080FF);
		_(Purple, 0xFF00FF); _(Magenta,   0xFF0080); _(Lilac,      0x8000FF);
	};
#undef _
};

namespace Palette = Colors::Oxygen; 

constexpr Color Desaturate(const Color& clr, float factor)
{
	return (clr * (1-factor)) + (Color(clr.getLength()) * factor);
};

constexpr Color Saturate(const Color& clr, float factor)
{
	return (clr) - (clr * (Color(1.f)-clr).normalized())*factor;
};

constexpr Color Dark(const Color& clr, float factor=0.4f)
{
	return Saturate(clr, factor/2) * (1-factor);
};

constexpr Color Bright(const Color& clr, float factor=0.5f)
{
	return (clr * factor) + (Colors::White * factor);
};
