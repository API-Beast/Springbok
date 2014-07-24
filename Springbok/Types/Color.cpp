//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "Color.h"

namespace
{
	constexpr Vec3F RefWhite = {0.950470, 1.000000, 1.088830}; // CIE standard illuminant D65
	Vec3F Lab2RGB(Vec3F lab)
	{
		auto xyzComponent = [](double x) -> double
		{
			return x > 0.206893034 ? x * x * x : (x - 4.0 / 29.0) / 7.787037;
		};
		auto rgbComponent = [](double x) -> double
		{
			return x <= 0.0031308 ? 12.92 * x : 1.055 * Power(x, 1.0 / 2.4) - 0.055;
		};
		Vec3<double> xyz;
		double y = (lab[0] + 0.16) / 1.16;
		xyz[0] = xyzComponent((lab[1] / 5) + y);
		xyz[1] = xyzComponent(y);
		xyz[2] = xyzComponent(y - (lab[2] / 2));
		xyz *= RefWhite;
		Vec3F rgb;
		rgb[0] = rgbComponent( 3.2404542 * xyz[0] - 1.5371385 * xyz[1] - 0.4985314 * xyz[2]);
		rgb[1] = rgbComponent(-0.9692660 * xyz[0] + 1.8760108 * xyz[1] + 0.0415560 * xyz[2]);
		rgb[2] = rgbComponent( 0.0556434 * xyz[0] - 0.2040259 * xyz[1] + 1.0572252 * xyz[2]);
		return rgb;
	};
	
	Vec3F RGB2Lab()
	{
		
	};
};

Color HCL(Angle hue, float chroma, float luma)
{
	Vec3F lab = {luma, chroma*hue.cos(), chroma*hue.sin()};
	return Lab2RGB(lab);
}