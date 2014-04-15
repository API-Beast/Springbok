//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <cstdint>
#include <climits>

#include <ctime>
#include <Springbok/Geometry/Vec3.h>
#include <Springbok/Math/Operations.h>
#include <Springbok/Math/Range.h>
#include <Springbok/Geometry/Angle.h>

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
	float getFloat(); // float in [0.0, 1.0]
	template<class T> T getNumber(T min, T max);   // [min, max]
	template<class T> T getNumber(T max);          // [0, max]
	template<class T> T getNumber(Range<T> range); // [range.Start, range.End]
	//~!
	Angle getNumber(Angle min, Angle max);

	//~ These functions generate a random number for every component of the vector and return them, again in a vector.
	template<typename T = float> Vec2<T> getVec2(Vec2<T> min, Vec2<T> max);
	template<typename T = float> Vec3<T> getVec3(Vec3<T> min, Vec3<T> max);

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
//~!

inline float RandomNumberGenerator::getFloat()
{
	return generate() / double(UINT_MAX);
};

template<typename T>
T RandomNumberGenerator::getNumber(T max)
{
	return getNumber<T>(T(), max);
};

template<typename T>
T RandomNumberGenerator::getNumber(T min, T max)
{
	return min + getFloat() * (NextBiggerValue(max) - min);
}

template<typename T>
T RandomNumberGenerator::getNumber(Range<T> range)
{
	return getNumber(range.MinVal, range.MaxVal);
}

template<typename T>
Vec2<T> RandomNumberGenerator::getVec2(Vec2<T> min, Vec2<T> max)
{
	return Vec2<T>(min.X + getFloat() * (NextBiggerValue(max.X) - min.X), min.Y + getFloat() * (NextBiggerValue(max.Y) - min.Y));
};

template<typename T>
Vec3<T> RandomNumberGenerator::getVec3(Vec3<T> min, Vec3<T> max)
{
	return Vec3<T>(min.X + getFloat() * (NextBiggerValue(max.X) - min.X), min.Y + getFloat() * (NextBiggerValue(max.Y) - min.Y), min.Z + getFloat() * (NextBiggerValue(max.Z) - min.Z));
};