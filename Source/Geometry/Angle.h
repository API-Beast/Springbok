// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "Vec2.h"
#include <Springbok/Math/Radian.h>

//! @ingroup Angle
//! @{
struct Angle
{
	Angle(float value);
	Angle(Radian value);
	Angle()=default;
	operator float() const;
	operator Radian() const;
	Angle operator+(float value) const;
	Angle operator-(float value) const;
	float operator*(float value) const;
	float operator/(float value) const;
	Angle& operator+=(float value);
	Angle& operator-=(float value);
	Angle& operator*=(float value);
	Angle& operator/=(float value);
	Angle operator-() const;
	bool operator >(Angle other) const;
	bool operator <(Angle other) const;
	bool operator==(Angle other) const;
	bool operator!=(Angle other) const;
	bool operator>=(Angle other) const;
	bool operator<=(Angle other) const;
	bool operator >(float other) const{ return operator >(Angle(other)); };
	bool operator <(float other) const{ return operator <(Angle(other)); };
	bool operator==(float other) const{ return operator==(Angle(other)); };
	bool operator!=(float other) const{ return operator!=(Angle(other)); };
	bool operator>=(float other) const{ return operator>=(Angle(other)); };
	bool operator<=(float other) const{ return operator<=(Angle(other)); };
	static Angle FromRadians(float radians);
	static Angle FromDegree (float degree);
	Radian toRadians() const;
 	float toDegree() const;
	float difference(Angle other) const;
	Angle average(Angle other, float factor) const;
	Vec2F toDirection(Vec2F up=Vec2F(0.0f, -1.0f)) const;
public:
	static Angle FromBooleanDirectionMatrix(bool up, bool right, bool down, bool left);
private:
	float angle=0.f;
};
//! @}