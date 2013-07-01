// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <vector>
#include "Color.h"

struct ColorPalette;

//! @ingroup Color
template<typename T>
using ColorPaletteBlueprint = std::vector<T>;

//! @ingroup Color
struct ColorPalette : public std::vector<ColorRGB>
{
	template<typename Color>
	static ColorPalette GenerateFromBlueprint(Color base, ColorPaletteBlueprint<Color> blueprint);
};

template<typename Color>
ColorPalette ColorPalette::GenerateFromBlueprint(Color base, ColorPaletteBlueprint<Color> blueprint)
{
	ColorPalette result;
	result.reserve(blueprint.size());
	for(const Color& color : blueprint) result.push_back(base.addTint(color));
	return result;
}
//! @}