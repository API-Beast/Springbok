//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "Noise.h"
#include "../Math/Range.h"

float Noise1D::calc(float index)
{
	float value = 1.f;
	auto valueAt = [this](float point, int octave){ return RandomNumberGenerator(Seed ^ int(point * 37892 * octave)).getFloat(); };
	for(int i = 1; i <= Octaves; ++i)
	{
		float interval = Interval / Power<2>(i);
		RangeF bounds = RangeF::FromInterval(index, interval);
		float start = valueAt(bounds.MinVal, i);
		float end   = valueAt(bounds.MaxVal, i);
		float factor = (index - bounds.MinVal) / interval;
		float curOctaveValue = start + (end - start) * factor;
		float curOctaveInfluence = 1 / Power<2>(i);
		curOctaveValue = (curOctaveValue * curOctaveInfluence) + (1 - curOctaveInfluence);
		value *= curOctaveValue;
	}
	return value;
}