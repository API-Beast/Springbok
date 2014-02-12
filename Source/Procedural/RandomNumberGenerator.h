//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <cstdint>
#include <climits>

#include <time.h>
#include <Springbok/Geometry/Vec2.h>

class RandomNumberGenerator
{
public:
	RandomNumberGenerator(int seed = static_cast<unsigned int>(time(0)));
	float generate(){ return generateBitfield() / double(UINT_MAX); };
	template<typename T=float>
	T generate(T min, T max){ return min + generate()*(max-min); };
	template<typename T=float>
	Vec2<T> generateVec2(Vec2<T> min, Vec2<T> max){ return Vec2<T>(min.X + generate()*(max.X-min.X), min.Y + generate()*(max.Y-min.Y)); };
	unsigned int generateBitfield();
public:
	unsigned int HighSeed;
	unsigned int LowSeed;
};