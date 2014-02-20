// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#include "Color.h"
#include  <cmath>

#define PI 3.14159265358979323846

Color HSY(float Hue, float Saturation, float Luma)
{	
	float ma[3] = {+1.0000, +1.0000, +1.0000};
	float mb[3] = {+0.7010, -0.2990, -0.2990};
	float mc[3] = {+0.2731, -0.3043, +0.8504};
	float chroma, c1, c2;
	Color saturated;
	Color unsaturated = Vec3F(Luma);
	
	float lumaMatch = (1 - Saturation) * Luma;
	
	chroma = (1.7320508 * Saturation) / fmod(-(Hue / 6 * PI), 1.f);
	c1 =  chroma * cos(Hue * PI * 2);
	c2 = -chroma * sin(Hue * PI * 2);
	
	saturated[0] = ma[0] * Luma + mb[0] * c1 + mc[0] * c2;
	saturated[1] = ma[1] * Luma + mb[1] * c1 + mc[1] * c2;
	saturated[2] = ma[2] * Luma + mb[2] * c1 + mc[2] * c2;
	return (unsaturated * (1-Saturation)) + (saturated * Saturation);
}