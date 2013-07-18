#pragma once
#include "Easing.h"

enum class Interpolation
{
	Constant,
	Linear,
	Cubic,
	AutoEase
};

template<typename T>
T InterpolateLinear(const T& start, const T& end, float factor)
{
	return start + (end - start) * factor;
};

template<typename T>
T InterpolateLinear(const T& startV, const T& endV, float start, float end, float cur)
{
	return InterpolateLinear<T>(startV, endV, (cur-start)/(end-start));
};

template<typename T>
T InterpolateCubic(const T& prev, const T& start, const T& end, const T& after, float factor)
{
	// Don't ask me for proper names for these variables or the logic behind them, this is math.
	// And I have no idea about math.
	// If somebody has a non-math (e.g. written in logic, not math) explanation for Cubic Interpolation, I would be grateful.
	T a0, a1, a2;
	a0 = after - end - prev + start;
	a1 = prev - start - a0;
	a2 = end - prev;
	return start + (a0 * factor*factor*factor) + (a1 * factor*factor) + (a2 * factor);
};

template<typename T>
T Interpolate(Interpolation kind, const T& prev, const T& start, const T& end, const T& after, float factor, const EasingFunctionBase& func = LinearEasing())
{
	switch(kind)
	{
		case Interpolation::Constant:
			return start;
		case Interpolation::Linear:
			return InterpolateLinear<T>(start, end, factor);
		case Interpolation::Cubic:
			return InterpolateCubic<T>(prev, start, end, after, factor);
		case Interpolation::AutoEase:
			T slopeCurrent  =   end - start;
			T slopePrevious = start - prev;
			T slopeNext     = after - end;
			if(slopeCurrent > slopePrevious)
			{
				// Bigger than last, but less than next: Continous, don't interpolate
				if(slopeCurrent < slopeNext)
					return InterpolateLinear(start, end, factor);
				// Next slope is less than current: Slow down, ease out
				else
					return func.easeOut(InterpolateLinear(start, end, factor));
			}
			else
			{
				// Slower than last & slower than next: Speed up, ease in
				if(slopeCurrent < slopeNext)
					return func.easeIn(InterpolateLinear(start, end, factor));
				// Faster than next, but slower than last: Neutral
				else
					return func.easeInOut(InterpolateLinear(start, end, factor));
			}
		break;
	}
};

template<typename T>
T Interpolate(Interpolation kind, const T& start, const T& end, float factor, const EasingFunctionBase& func = LinearEasing())
{
	return Interpolate<T>(kind, start - (end - start), start, end, end + (end - start), factor, func);
}

template<typename T>
T Interpolate(Interpolation kind, const T& prev, const T& start, const T& end, const T& after, float startT, float endT, float curT, const EasingFunctionBase& func = LinearEasing())
{
	return Interpolate<T>(kind, prev, start, end, after, (curT-startT)/(endT-startT), func);
};