//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <stdint.h>

//~ ### RandomNumberGenerator
//~ *Dependencies: Standard headers only (stdint.h, math.h, limits.h)*
//~
//~ A minimal and very fast generator for pseudo-random numbers based on [GameRand](http://goo.gl/jKX3nV).
class RandomNumberGenerator
{
public:
	//~ #### Constructors
	//~ These all set the seed to the specified parameters.
	RandomNumberGenerator(uint32_t seed);  // Derive the 64-Bit seed from a 32-Bit seed.
	RandomNumberGenerator(uint32_t lowSeed, uint32_t highSeed);
	
	//~ #### Generator Functions
	//~ Generate random numbers inside a specific range, this Range is always inclusive. (E.g. it is always possible that it returns the max value itself.)
	float randFloat();                     // float in [0.0, 1.0]
	float randFloat(float min, float max); // [min, max]
	float randFloat(float max);            // [0, max]
	
	int randInt(int max);
	int randInt(int min, int max);

	//~ Generates 32 random bits, all other generator functions are based on this one.
	uint32_t generate();
public:
	//~ #### Member Variables
	uint32_t HighSeed; // First 32 Bits of the Seed.
	uint32_t LowSeed;  // Last  32 Bits of the Seed.
};
