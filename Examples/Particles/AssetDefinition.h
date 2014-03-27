//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "ParticleSystem.h"
#include <Springbok/Graphics/BitmapFont.h>

struct AssetDefinition
{
	// Fonts
	BitmapFont SmallFont;

	// Particles
	ParticleDefinition Spark;
	
public:
	void initAll();
	void initParticles();
};

extern AssetDefinition gAssets;

