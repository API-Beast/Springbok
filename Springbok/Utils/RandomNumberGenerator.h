//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <Springbok/Foundation/Vec3.h>

#include <ctime>

//~ ## class RandomNumberGenerator
//~ A minimal & cheap generator for pseudo-random numbers.
class RandomNumberGenerator
{
public:
	//~ ### Constructors
	//~ These all set the seed to the specified parameters.
	RandomNumberGenerator(unsigned int seed = unsigned(std::time(0)));  // Derive the 64-Bit seed from a 32-Bit seed. If no seed is given use the system time as seed.
	RandomNumberGenerator(unsigned int lowSeed, unsigned int highSeed);
	RandomNumberGenerator(unsigned long long int fullSeed);
	
	//~ ### Generator Functions
	//~ Generate random numbers inside a specific range, this Range is always inclusive. (E.g. it is always possible that it returns the max value itself.)
	float randFloat();                     // float in [0.0, 1.0]
	float randFloat(float min, float max); // [min, max]
	float randFloat(float max);            // [0, max]
	
	int randInt(int max);
	int randInt(int min, int max);

	//~ These functions generate a random number for every component of the vector and return them, again in a vector.
	Vec2F randVec2F(){ return randVec2F(0.f, 1.f); };
	Vec3F randVec3F(){ return randVec3F(0.f, 1.f); };
	Vec2F randVec2F(Vec2F max){ return randVec2F(0.f, max); };
	Vec3F randVec3F(Vec3F max){ return randVec3F(0.f, max); };
	Vec2F randVec2F(Vec2F min, Vec2F max);
	Vec3F randVec3F(Vec3F min, Vec3F max);

	//~ Generates 32 random bits, all other generator functions are based on this one.
	unsigned int generate();
public:
	//~ ### Member Variables
	unsigned int HighSeed; // First 32 Bits of the Seed.
	unsigned int LowSeed;  // Last  32 Bits of the Seed.
};

//~ ### Global Variables
//~ Outside of class scope
extern RandomNumberGenerator gRNG; // A global, default-initialized instance of the RandomNumberGenerator for convinience.