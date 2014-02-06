// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#include "Angle.h"
#include <Springbok/Math/Operations.h>

Vec2F Angle::toDirection(Vec2F up) const
{
	return up.rotated(*this);
}

float Angle::toDegree() const
{
	return angle * 360;
}

Angle::Angle(float value)
{
	while(value < 0.f)
	{
		value = 1.f + value;
	}
	angle = std::fmod(value, 1.f);
}

Angle::Angle(Radian value)
{
	float val=value / Tau;
	while(val < 0.f)
	{
		val = 1.f + val;
	}
	angle = std::fmod(val, 1.f);
}

Angle::operator float() const
{
	return angle;
}

Angle::operator Radian() const
{
	return angle * Tau;
}

Angle Angle::operator+(float value) const
{
	return angle + value;
}

Angle Angle::operator-(float value) const
{
	return angle - value;
}

Angle Angle::operator*(float value) const
{
	return angle * value;
}

Angle Angle::operator/(float value) const
{
	return angle / value;
}

Angle& Angle::operator+=(float value)
{
	angle += value;
	angle = Modulo(angle, 1.f);
	return *this;
}

Angle& Angle::operator-=(float value)
{
	angle -= value;
	angle = Modulo(angle, 1.f);
	return *this;
}

Angle& Angle::operator*=(float value)
{
	angle *= value;
	angle = Modulo(angle, 1.f);
	return *this;
}

Angle& Angle::operator/=(float value)
{
	angle /= value;
	angle = Modulo(angle, 1.f);
	return *this;
}

Angle Angle::operator-() const
{
	return angle+0.5;
}

float Angle::difference(Angle other) const
{
	if(other.angle < angle) return -other.difference(*this);
	float differenceA = other.angle - angle;
	float differenceB = 1 - differenceA;
	if(differenceA > differenceB)
		return -differenceB;
	else
		return differenceA;
}

bool Angle::operator>(Angle other) const
{
	return difference(other) > 0.f && other.angle != this->angle;
}

bool Angle::operator<(Angle other) const
{
	return difference(other) < 0.f && other.angle != this->angle;
}

bool Angle::operator==(Angle other) const
{
	return this->angle == other.angle;
}

bool Angle::operator!=(Angle other) const
{
	return this->angle != other.angle;
}

bool Angle::operator>=(Angle other) const
{
	return *this > other || *this == other;
}

bool Angle::operator<=(Angle other) const
{
	return *this < other || *this == other;
}

Angle Angle::FromDegree(float degree)
{
	return degree / 360;
}

Angle Angle::FromRadians(float radians)
{
	return radians / Tau;
}

Radian Angle::toRadians() const
{
	return angle * Tau;
}

Angle Angle::average(Angle other, float factor) const
{
	//if(other.angle > this->angle) return other.average(*this, 1-factor);
	float diff = difference(other);
	return (*this) + diff*factor;
}
