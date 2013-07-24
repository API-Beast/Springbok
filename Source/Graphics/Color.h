// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <Springbok/Geometry/Angle.h>

//! @addtogroup groupColor
//! @{

struct ColorRGB;
struct TintHSY;

/** A color in the RGB color space which is closest to the way a monitor displays a pixel and generally how light works. */
struct ColorRGB
{
	constexpr ColorRGB()=default;
	constexpr ColorRGB(float r, float g, float b) : Red(r), Green(g), Blue(b){};
	float Red   = 0.0f;
	float Green = 0.0f;
	float Blue  = 0.0f;
	/** Blend between \a this and \a other with a opacity of \a factor. */
	ColorRGB blend(const ColorRGB& other, float factor);
	/** Clip all components to \c 0...1 range. */
	ColorRGB clip();
};

typedef ColorRGB Color; /**< @related ColorRGB */

/** A color in a Hue/Saturation/Luma color space. This is the a very convenient and predictable color space for generating patterns of colors. */
struct ColorHSY
{
	ColorHSY(float h, float s, float y);
	/** The Hue of the color. \c 0.00 is Red, \c 0.33 is Blue, \c 0.66 is Green and \c 1.00 is Red again. */
	Angle Hue;
	/** The Saturation of the color. \c 0.0 will make the color look Grey, \c 1.0 will make the color look vibrant. */
	float Saturation;
	/** The Luma or perceived Brightness of the color. \c 0.0 is Black. \c 1.0 is rather bright. This depends on on the Saturation and the Hue. For a color with Saturation \c 0.0 it is White */
	float Luma;
	/** Conversion to ColorRGB. */
	operator ColorRGB() const;
	ColorHSY tint(const TintHSY& other) const;
};

struct TintHSY
{
	Angle HueShift = 0.0f;
	float SaturationMult = 1.0f;
	float SaturationAdd  = 0.0f;
	float LumaMult = 1.0f;
	float LumaAdd  = 0.0f;
};

namespace Colors
{
	namespace Saturated
	{
		static constexpr ColorRGB Red   = ColorRGB(1.0f, 0.0f, 0.0f);
		static constexpr ColorRGB Green = ColorRGB(0.0f, 1.0f, 0.0f);
		static constexpr ColorRGB Blue  = ColorRGB(0.0f, 0.0f, 1.0f);
		
		static constexpr ColorRGB Yellow = ColorRGB(1.0f, 1.0f, 0.0f);
		static constexpr ColorRGB Orange = ColorRGB(1.0f, 0.5f, 0.0f);
		static constexpr ColorRGB Lime   = ColorRGB(0.5f, 1.0f, 0.0f);
		
		static constexpr ColorRGB Cyan       = ColorRGB(0.0f, 1.0f, 1.0f);
		static constexpr ColorRGB Turquoise  = ColorRGB(0.0f, 1.0f, 0.5f);
		static constexpr ColorRGB Aquamarine = ColorRGB(0.0f, 0.5f, 1.0f);
		
		static constexpr ColorRGB Purple  = ColorRGB(1.0f, 0.0f, 1.0f);
		static constexpr ColorRGB Magenta = ColorRGB(1.0f, 0.0f, 0.5f);
		static constexpr ColorRGB Lilac   = ColorRGB(0.5f, 0.0f, 1.0f);
	};
	
	static constexpr ColorRGB White = ColorRGB(1.0f, 1.0f, 1.0f);
	static constexpr ColorRGB Grey  = ColorRGB(0.5f, 0.5f, 0.5f);
	static constexpr ColorRGB Black = ColorRGB(0.0f, 0.0f, 0.0f);
};

//! @}