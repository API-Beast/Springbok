//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "Noise.h"

float Noise1D::calc(float index)
{
	float value = 1.f;
	auto valueAt = [this](float point, int octave){ return RandomNumberGenerator(Seed ^ int(point * 37892 * octave)).randFloat(); };
	for(int i = 1; i <= Octaves; ++i)
	{
		float interval = Interval / (i * i);
		float minVal = interval * int(index/interval);
		float maxVal = minVal + interval;
		float start = valueAt(minVal, i);
		float end   = valueAt(maxVal, i);
		float factor = (index - minVal) / interval;
		float curOctaveValue = start + (end - start) * factor;
		float curOctaveInfluence = 1 / (i * i);
		curOctaveValue = (curOctaveValue * curOctaveInfluence) + (1 - curOctaveInfluence);
		value *= curOctaveValue;
	}
	return value;
}