#pragma once
#include "Easing.h"

enum Interpolation
{
	Constant,
	Linear,
	Eased,
	Quadratic,
	Cubic
};

struct InterpolationData
{
	Interpolation  Type;
	EasingFunction Easing;
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
T InterpolateEased(const T& start, const T& end, float factor, EasingFunction func)
{
	return start + (end - start) * (*func)(factor);
};

template<typename T>
T InterpolateEased(const T& startV, const T& endV, float start, float end, float cur, EasingFunction func)
{
	return InterpolateEased<T>(startV, endV, (cur-start)/(start-end));
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