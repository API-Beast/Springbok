//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "AssetDefinition.h"

void AssetDefinition::initAll()
{
	initParticles();
}

void AssetDefinition::initParticles()
{
	Image spriteSheet("Particles.png");
	Image spark = spriteSheet.cut({0, 0}, {16, 16});
	
	// ------------------------------------------------------------------
	// ### Spark
	// ------------------------------------------------------------------
	{
		auto& d = Spark;
		d.Sprite = spark;
		d.Color.insert(0.0f, {1.f, 1.f, 1.f, 1.00f});
		d.Color.insert(0.5f, {1.f, 1.f, 1.f, 0.50f});
		d.Color.insert(1.0f, {1.f, 1.f, 1.f, 0.05f});
	}
}

AssetDefinition gAssets;