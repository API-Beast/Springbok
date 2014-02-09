//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "RandomNumberGenerator.h"

RandomNumberGenerator::RandomNumberGenerator(int seed)
{
	LowSeed = seed;
	HighSeed = seed ^ 0x49616E42;
}

unsigned int RandomNumberGenerator::generateBitfield()
{
	static const int shift = sizeof(int) / 2;
	HighSeed = (HighSeed >> shift) + (HighSeed << shift);
	HighSeed += LowSeed;
	LowSeed += HighSeed;
	return HighSeed;
}