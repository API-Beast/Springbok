// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <Springbok/Types/Vec3.h>

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

Color HSV(float hue, float saturation, float value);
Color HSL(float hue, float saturation, float lightness);
Color HSY(float hue, float saturation, float luma);

namespace Colors
{
	static constexpr Color White = Color(1.0f);
	static constexpr Color Black = Color(0.0f);
	
#define _(NAME, CODE) static constexpr Color NAME = HTMLColor(CODE)
#define ___(NAME, CODEA, CODEB, CODEC) static constexpr Color NAME[] = {HTMLColor(CODEA), HTMLColor(CODEB), HTMLColor(CODEC)}
	// Palette from the KDE default icon theme. Good general purpose palette.
	// http://techbase.kde.org/Projects/Oxygen/Style#Color_Usage
	// High contrast, Saturated
	namespace Oxygen
	{
		_(Brown,      0x866327);
		_(Red,        0xE70F00);
		_(Magenta,    0xE70082);
		_(Lilac,      0xAD3696);
		_(BlueLilac,  0x583796);
		_(Blue,       0x0069BA);
		_(Cyan,       0x008990);
		_(SeaGreen,   0x00A778);
		_(Green,      0x48B13C);
		_(Yellow,     0xFFE300);
		_(Orange,     0xEF8441);
		
		namespace Vibrant
		{
			_(Orange, 0xff7e00);
			_(Red,    0xff0000);
			_(Pink,   0xff00bf);
			_(Lilac,  0x8000ff);
			_(Blue,   0x0066ff);
			_(Green,  0x00ff00);
			_(Lime,   0xc8ff00); // Replaced due to lack of difference to Yellow
			_(Yellow, 0xffff00);
		};
		
		___(Grey, 0x3E4547, 0x989A95, 0xF1F1EF);
	};
	
	// Dawnbringer 32 Color Palette reduced to 21 colors
	// Neutral, Muted
	namespace Dawnbringer
	{
		___(Purple,    0x45283C, 0x76428A, 0xD77BBA);
		___(Red,       0xAC3232, 0xD95763, 0xDF7126);
		___(Yellow,    0x8A6f30, 0x8F974A, 0xFBF236);
		___(Green,     0x4B692F, 0x37946E, 0x99E550);
		___(Blue,      0x3F3F74, 0x5B6EE1, 0x5FCDE4);
		___(Turquoise, 0x323C39, 0x306082, 0x37946E);
		
		___(Silver,  0x595652, 0x848e93, 0xb7c4df);
		___(Clay,    0x663931, 0x8F563B, 0xD9A066);
		___(Shadow,  0x11101B, 0x222034, 0x323c39);
	}
	
	// 100% Saturated colors; might not be the most appealing ones, visually.
	// Oversaturated, only suitable for Z-Spectrum games
	namespace Saturated
	{
		_(Red,    0xFF0000); _(Green,     0x00FF00); _(Blue,       0x0000FF);
		_(Yellow, 0xFFFF00); _(Orange,    0xFF8000); _(Lime,       0x80FF00);
		_(Cyan,   0x00FFFF); _(Turquoise, 0x00FF80); _(Aquamarine, 0x0080FF);
		_(Purple, 0xFF00FF); _(Magenta,   0xFF0080); _(Lilac,      0x8000FF);
	};
#undef _
#undef ___
};

namespace Palette = Colors::Oxygen; 

constexpr Color Desaturate(const Color& clr, float factor)
{
	return (clr * (1-factor)) + (Color(clr.length()) * factor);
};

constexpr Color Saturate(const Color& clr, float factor)
{
	return (clr) - (clr * (Color(1.f)-clr).normalized())*factor;
};

constexpr Color ShiftHueLeft(const Color& clr, float factor)
{
	return clr;
};

constexpr Color ShiftHueRight(const Color& clr, float factor)
{
	return clr;
};

constexpr Color Dark(const Color& clr, float factor=0.4f)
{
	return Saturate(clr, factor/2) * (1-factor);
};

constexpr Color Bright(const Color& clr, float factor=0.5f)
{
	return (clr * factor) + (Colors::White * factor);
};