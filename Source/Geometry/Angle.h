// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "Vec2.h"
#include <cmath>

//! A half turn in radians. Equal to the ratio of a circle's circumference to it's diameter.
constexpr float PI  = 3.14159;
//! A full turn in radians. Equal to the ratio of a circle's circumference to it's radius.
constexpr float Tau = PI * 2;

//! @ingroup Angle
//! @{
struct Angle
{
	explicit constexpr Angle(float value) : Data((PositiveModulo(value, Tau) > PI) ? (PositiveModulo(value, Tau) - Tau) : PositiveModulo(value, Tau)){};
	explicit Angle(Vec2F vec, Vec2F up=Vec2F(0.0f, -1.0f));
	Angle()=default;
	explicit operator float() const;
	Angle operator+(Angle value) const;
	Angle operator-(Angle value) const;
	Angle operator*(float value) const;
	Angle operator/(float value) const;
	Angle& operator+=(Angle value);
	Angle& operator-=(Angle value);
	Angle& operator*=(float value);
	Angle& operator/=(float value);
	Angle operator-() const;
	Angle operator+() const;
	bool operator >(Angle other) const;
	bool operator <(Angle other) const;
	bool operator==(Angle other) const;
	bool operator!=(Angle other) const;
	bool operator>=(Angle other) const;
	bool operator<=(Angle other) const;
	static constexpr Angle FromTurn  (float turns);
	static constexpr Angle FromRadians(float radians);
	static constexpr Angle FromDegree (float degree);
	float toRadians() const;
 	float toDegree() const;
	float toTurn() const;
	Vec2F toDirection() const;
	Vec2F rotateVec(Vec2F vec) const;
	void sanitize();
	
	constexpr double const sin() const;
	constexpr double const cos() const;
	static Angle Atan2(double a, double b);
	static Angle Acos(double A);
	static Angle Asin(double A);
	
public:
	static Angle FromBooleanDirectionMatrix(bool up, bool right, bool down, bool left);
public:
	float Data=0.f;
};

Angle operator*(float value, Angle angle);
Angle operator/(float value, Angle angle);

#include "Angle_constexpr.h"

// User defined suffixes should actually start with a underscore, but fuck the system.
constexpr Angle operator "" _turn(long double num){ return Angle::FromTurn(num); };
constexpr Angle operator "" _turn(unsigned long long num){ return Angle::FromTurn(num); };
constexpr Angle operator "" _deg(long double num){ return Angle::FromDegree(num); };
constexpr Angle operator "" _deg(unsigned long long num){ return Angle::FromDegree(num); };
constexpr Angle operator "" _rad(long double num){ return Angle::FromRadians(num); };
constexpr Angle operator "" _rad(unsigned long long num){ return Angle::FromRadians(num); };

std::ostream& operator<< (std::ostream& stream, const Angle obj);

//! @}