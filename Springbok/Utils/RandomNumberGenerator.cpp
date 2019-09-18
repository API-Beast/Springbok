//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "RandomNumberGenerator.h"
#include <math.h>
#include <limits.h>

namespace
{
	uint32_t hash(uint32_t a)
	{
		a = (a+0x7ed55d16) + (a<<12);
		a = (a^0xc761c23c) ^ (a>>19);
		a = (a+0x165667b1) + (a<<5);
		a = (a+0xd3a2646c) ^ (a<<9);
		a = (a+0xfd7046c5) + (a<<3);
		a = (a^0xb55a4f09) ^ (a>>16);
		return a;
	}
}

// Based on http://www.redditmirror.cc/cache/websites/mjolnirstudios.com_7yjlc/mjolnirstudios.com/IanBullard/files/79ffbca75a75720f066d491e9ea935a0-10.html
RandomNumberGenerator::RandomNumberGenerator(uint32_t seed)
{
	// The Problem with this RNG is that very similar seeds result in very similar results, making it not suitable for passing arbitary information as seed, we try to fix this by applying a hash function to the seed.
	uint32_t h = hash(seed);
	LowSeed = h ^ 0x520AF59;
	HighSeed = h ^ 0x49616E42;
}

RandomNumberGenerator::RandomNumberGenerator(uint32_t lowSeed, uint32_t highSeed)
{
	LowSeed = hash(lowSeed);
	HighSeed = hash(highSeed);
}

uint32_t RandomNumberGenerator::generate()
{
	static const int shift = sizeof(uint32_t)/2 * 8;
	HighSeed =  (HighSeed >> shift) + (HighSeed << shift);
	HighSeed += LowSeed;
	LowSeed  += HighSeed;
	return HighSeed;
}

int RandomNumberGenerator::randInt(int max)
{
	return randInt(0, max);
}

int RandomNumberGenerator::randInt(int min, int max)
{
	return min + randFloat() * ((max+1) - min);
}

float RandomNumberGenerator::randFloat()
{
	return generate() / double(UINT32_MAX);
}

float RandomNumberGenerator::randFloat(float min, float max)
{
	// With max instead of the std::nextafterf max would be exclusive, e.g. it would never be reached.
	return min + randFloat() * (nextafterf(max, INFINITY) - min);
}

float RandomNumberGenerator::randFloat(float max)
{
	return randFloat(0.f, max);
}
