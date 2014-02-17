// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#include "Color.h"
#include <Springbok/Math/Operations.h>

ColorRGB ColorRGB::blend(const ColorRGB& other, float factor)
{
	return ColorRGB(Red * (1 - factor) + other.Red * factor, Green * (1 - factor) + other.Green * factor, Blue * (1 - factor) + other.Blue * factor).clip();
}

ColorRGB ColorRGB::clip()
{
	return ColorRGB{BoundBy(0.f, Red, 1.f), BoundBy(0.f, Green, 1.f), BoundBy(0.f, Blue, 1.f)};
}

ColorHSY::operator ColorRGB() const
{	
	float ma[3] = {+1.0000, +1.0000, +1.0000};
	float mb[3] = {+0.7010, -0.2990, -0.2990};
	float mc[3] = {+0.2731, -0.3043, +0.8504};
	float chroma, c1, c2;
	ColorRGB saturated;
	ColorRGB unsaturated={Luma, Luma, Luma};
	
	float lumaMatch = (1 - Saturation) * Luma;
	
	chroma = (1.7320508 * Saturation) / fmod(-(Hue / 6 * PI), 1.f);
	c1 =  chroma * cos(Hue * Tau);
	c2 = -chroma * sin(Hue * Tau);
	
	saturated.Red   = ma[0] * Luma + mb[0] * c1 + mc[0] * c2;
	saturated.Green = ma[1] * Luma + mb[1] * c1 + mc[1] * c2;
	saturated.Blue  = ma[2] * Luma + mb[2] * c1 + mc[2] * c2;
	return unsaturated.blend(saturated, Saturation).clip();
}

ColorHSY ColorHSY::tint(const TintHSY& t) const
{
	return ColorHSY{Hue + t.HueShift, BoundBy(0.f, Saturation * t.SaturationMult + t.SaturationAdd, 1.f), BoundBy(0.f, Luma * t.LumaMult + t.LumaAdd, 1.f) };
}

ColorRGB ColorRGB::operator+(ColorRGB other) const
{
	return ColorRGB(Red+other.Red, Green+other.Green, Blue+other.Blue);
}

ColorRGB ColorRGB::operator-(ColorRGB other) const
{
	return ColorRGB(Red-other.Red, Green-other.Green, Blue-other.Blue);
}

ColorRGB ColorRGB::operator*(float factor) const
{
	return ColorRGB(Red*factor, Green*factor, Blue*factor);
}

bool ColorRGB::operator<(ColorRGB other) const
{
	return (Red+Green+Blue) < (other.Red+other.Green+other.Blue);
}

bool ColorRGB::operator>(ColorRGB other) const
{
	return (Red+Green+Blue) > (other.Red+other.Green+other.Blue);
}

bool ColorRGB::operator!=(ColorRGB other) const
{
	return (Red != other.Red) || (Blue != other.Blue) || (Green != other.Green);
}

bool ColorRGB::operator==(ColorRGB other) const
{
	return (Red == other.Red) && (Blue == other.Blue) && (Green == other.Green);
}
