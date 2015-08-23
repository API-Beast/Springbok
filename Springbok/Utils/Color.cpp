//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "Color.h"

Vec3F Lab2RGB(Vec3F lab)
{
	auto xyzComponent = [](double x) -> double
	{
		return Power<3>(x);
		//return x > 0.206893034 ? Power<3>(x) : (x - 4.0 / 29.0) / 7.787037;
	};
	auto rgbComponent = [](double x) -> double
	{
		return 1.055 * Root(x, 2.4) - 0.055;
		//return x <= 0.0031308 ? 12.92 * x : 1.055 * Root(x, 2.4) - 0.055;
	};
	Vec3<double> xyz;
	double y = (lab[0] + 0.16) / 1.16;
	xyz[0] = xyzComponent((lab[1] / 5) + y);
	xyz[1] = xyzComponent(y);
	xyz[2] = xyzComponent(y - (lab[2] / 2));
	// TODO: Figure this out, without this RGB to LAB to RGB works, with not
	//xyz *= RefWhiteD65;
	Vec3F rgb;
	rgb[0] = rgbComponent( 3.2404542 * xyz[0] - 1.5371385 * xyz[1] - 0.4985314 * xyz[2]);
	rgb[1] = rgbComponent(-0.9692660 * xyz[0] + 1.8760108 * xyz[1] + 0.0415560 * xyz[2]);
	rgb[2] = rgbComponent( 0.0556434 * xyz[0] - 0.2040259 * xyz[1] + 1.0572252 * xyz[2]);
	return rgb;
};

Vec3F RGB2Lab(Vec3F rgb)
{
	// The reverse of the formula in Lab2RGB
	auto xyzComponent = [](double x) -> double
	{
		return Root<3>(x);
		//return x > 0.008856 ? Root<3>(x) : 7.787037 * x + 4 / 29;
	};
	auto rgbComponent = [](double x) -> double
	{
		return Power((x + 0.055) / 1.055, 2.4);
		//return x <= 0.04045 ? x / 12.92 : Power((x + 0.055) / 1.055, 2.4);
	};
	Vec3<double> denRGB = rgb;
	denRGB[0] = rgbComponent(rgb[0]);
	denRGB[1] = rgbComponent(rgb[1]);
	denRGB[2] = rgbComponent(rgb[2]);
	Vec3<double> xyz;
	xyz[0] = xyzComponent(0.4124565 * denRGB[0] + 0.3575761 * denRGB[1] + 0.1804375 * denRGB[2]);
	xyz[1] = xyzComponent(0.2126729 * denRGB[0] + 0.7151522 * denRGB[1] + 0.0721750 * denRGB[2]);
	xyz[2] = xyzComponent(0.0193339 * denRGB[0] + 0.1191920 * denRGB[1] + 0.9503041 * denRGB[2]);
	// TODO: Figure this out, without this RGB to LAB to RGB works, with not
	//xyz /= RefWhiteD65;
	Vec3F lab;
	lab[0] = 1.16 * xyz[1] - 0.16;
	lab[1] = 5 * (xyz[0] - xyz[1]);
	lab[2] = 2 * (xyz[1] - xyz[2]);
	return lab;
};

Vec3F HCL(Angle hue, float chroma, float luma)
{
	Vec3F lab = {luma, chroma*hue.cos(), chroma*hue.sin()};
	return Lab2RGB(lab);
}

Vec4F Int2Color(unsigned int hex)
{
	union
	{
		unsigned int hex;
		Vec4C color;
	} val = {0};
	val.hex = {hex};
	return Vec4F(val.color) / 256.f;
}

unsigned int Color2Int(Vec4F clr)
{
	union
	{
		unsigned int hex;
		Vec4C color;
	} val = {0};
	val.color = {Vec4C(val.color * 256.f)};
	return val.hex;
}