//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once
#include <Springbok/Utils/RandomNumberGenerator.h>

#include <ctime>

// Fractal 1D-Perlin Noise
// I think...
struct Noise1D
{
	unsigned int Seed = std::time(0);// This seed will be used to initialize the noise
	int Octaves = 1;        // How many Octaves are used, the more octaves the finer the details.
	float Interval = 0.1f;  // How many Data points are sampled, each octave uses double the Data points as the previous one
	
	float calc(float index);
};