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
	explicit constexpr Angle(float value) : Data((PositiveModulo(value, 1.f) > 0.5f) ? (PositiveModulo(value, 1.f) - 1.0f) : PositiveModulo(value, 1.f)){};
	Angle(Radian value);
	Angle()=default;
	explicit operator float() const;
	operator Radian() const;
	Angle operator+(Angle value) const;
	Angle operator-(Angle value) const;
	Angle operator*(float value) const;
	Angle operator/(float value) const;
	Angle& operator+=(Angle value);
	Angle& operator-=(Angle value);
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
	static constexpr Angle FromRadians(float radians);
	static constexpr Angle FromDegree (float degree);
	Radian toRadians() const;
 	float toDegree() const;
	Vec2F toDirection(Vec2F up=Vec2F(0.0f, -1.0f)) const;
	void sanitize();
public:
	static Angle FromBooleanDirectionMatrix(bool up, bool right, bool down, bool left);
public:
	float Data=0.f;
};

constexpr Angle Angle::FromDegree(float degree)
{
	return Angle(degree / 360);
}

constexpr Angle Angle::FromRadians(float radians)
{
	return Angle(radians / Tau);
}

// User defined suffixes should actually start with a underscore, but fuck the system.
constexpr Angle operator "" _turn(long double num){ return Angle(num); };
constexpr Angle operator "" _turn(unsigned long long num){ return Angle(num); };
constexpr Angle operator "" _deg(long double num){ return Angle::FromDegree(num); };
constexpr Angle operator "" _deg(unsigned long long num){ return Angle::FromDegree(num); };
constexpr Angle operator "" _rad(long double num){ return Angle::FromRadians(num); };
constexpr Angle operator "" _rad(unsigned long long num){ return Angle::FromRadians(num); };

std::ostream& operator<< (std::ostream& stream, const Angle obj);

//! @}