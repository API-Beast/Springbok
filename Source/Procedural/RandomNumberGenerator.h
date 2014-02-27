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
#include <Springbok/Math/Operations.h>

class RandomNumberGenerator
{
public:
	RandomNumberGenerator(unsigned int seed = static_cast<unsigned int>(time(0)));
	RandomNumberGenerator(unsigned int lowSeed, unsigned int highSeed);
	RandomNumberGenerator(unsigned long long int fullSeed);
	float getFloat();
	template<typename T=float> T getNumber(T max){ return getNumber<T>(T(), max); };
	template<typename T=float> T getNumber(T min, T max);
	template<typename T=float> Vec2<T> getVec2(Vec2<T> min, Vec2<T> max);
	unsigned int generate();
public:
	unsigned int HighSeed;
	unsigned int LowSeed;
};

inline float RandomNumberGenerator::getFloat()
{
	return generate() / double(UINT_MAX);
};

template<typename T>
T RandomNumberGenerator::getNumber(T min, T max)
{
	return min + getFloat()*(NextBiggerValue(max) - min);
}

template<typename T>
Vec2<T> RandomNumberGenerator::getVec2(Vec2<T> min, Vec2<T> max)
{
	return Vec2<T>(min.X + getFloat()*(NextBiggerValue(max.X)-min.X), min.Y + getFloat()*(NextBiggerValue(max.Y)-min.Y));
};