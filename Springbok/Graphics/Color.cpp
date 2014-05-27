// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#include "Color.h"
#include  <Springbok/Math/Operations.h>
#include  <Springbok/Types/Angle.h>

#define PI 3.14159265358979323846

Color HSY(float hue, float Saturation, float Luma)
{	
	Angle Hue = Angle::FromTurn(hue);
	float lumaMatch = (1 - Saturation) * Luma; // <- What is this? I don't know anymore :(
	float chromaPhase = (SquareRoot(3) * Saturation) * Modulo(Hue.Data, 1.f);
	static const Vec3F modCos = {+0.7010, -0.2990, -0.2990};
	static const Vec3F modSin = {+0.2731, -0.3043, +0.8504};
	
	Color saturated = Luma + modCos * (chromaPhase * Hue.cos()) + modSin * (chromaPhase * -Hue.sin());
	return ((Luma * (1-Saturation)) + (saturated * Saturation)).upperBound(1.f).lowerBound(0.f);
};

float sawTooth(float x, float frequency)
{
	return Modulo(x, 1.f);
}

Color HSV(float hue, float saturation, float value)
{
};