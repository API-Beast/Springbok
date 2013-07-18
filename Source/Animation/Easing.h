#pragma once
#include <Springbok/Math/Operations.h>

class EasingFunctionBase
{
public:
	
	virtual float easeIn   (float val) const
	{
		return val;
	};
	
	virtual float easeOut  (float val) const
	{
		return easeIn(1-val);
	};
	
	virtual float easeInOut(float val) const
	{
		if(val < 0.5)
			return easeIn(val*2)*0.5;
		return 0.5 + easeOut((val-0.5)*2)*0.5;
	};
};

using LinearEasing = EasingFunctionBase;

struct SinusEasing : public EasingFunctionBase
{
	float easeIn(float val) const
	{
		return Sin(val * PI/4) * (1/Sin(PI/4));
	};
};

struct PowerEasing : public EasingFunctionBase
{
	PowerEasing(float power = 2) : ToPower(power){};
	float ToPower;
	
	float easeIn(float val) const
	{
		return Power(val, ToPower);
	};
};