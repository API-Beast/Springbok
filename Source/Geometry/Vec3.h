//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "Vec2.h"

template<typename T>
struct Vec3
{
public:
	union
	{
		T Val[3];
		struct
		{
			T X;
			T Y;
			T Z;
		};
	};
	
	constexpr Vec3() : X(), Y(), Z() {};
	template<typename P>
	constexpr Vec3(const P& val) : X(val), Y(val), Z(val) {};
	template<typename P>
	constexpr Vec3(const Vec3<P>& other) : X(other.X), Y(other.Y), Z(other.Z) {};
	template<typename P1, typename P2, typename P3>
	constexpr Vec3(const P1& vx, const P2& vy, const P3& vz) : X(vx), Y(vy), Z(vz) {};
	
	T& operator[](int x);
	const T& operator[](int x) const;
	template<typename P> constexpr bool operator==(const Vec3<P>& other){ return X == other.X && Y == other.Y && Z == other.Z;};
	template<typename P> constexpr bool operator!=(const Vec3<P>& other){ return X != other.X || Y != other.Y || Z != other.Z;};
	template<typename P> constexpr bool operator >(const Vec3<P>& other) { return X > other.X || Y > other.Y || Z > other.Z;  };
	template<typename P> constexpr bool operator <(const Vec3<P>& other) { return X < other.X && Y < other.Y && Z < other.Z;  };
	constexpr Vec3<T> operator-() const; //!< Returns the opposite of this vector. Equals Vec2(-X, -Y).
	
	constexpr float sqLength() const;
	constexpr float   length() const;  //!< Returns the \c length of this vector. This is the distance to Vec3(0, 0, 0).
	constexpr Vec3<T> normalized() const;          //!< Returns the normalized version of \c this. A normalized vector (also called unit vector) has a length of 1 or 0.
	
	Vec3<T> lowerBound(Vec3<T> other) const;
	Vec3<T> upperBound(Vec3<T> other) const;
	
	constexpr bool isNull() const;
	
	constexpr Vec2<T> XY() const{ return {X, Y}; };
	constexpr Vec2<T> YX() const{ return {Y, X}; };
	constexpr Vec2<T> XX() const{ return {X, X}; };
	constexpr Vec2<T> YY() const{ return {Y, Y}; };
	
	constexpr Vec2<T> ZY() const{ return {Z, Y}; };
	constexpr Vec2<T> ZX() const{ return {Z, X}; };
	constexpr Vec2<T> ZZ() const{ return {Z, Z}; };
	
	constexpr Vec3<T> XXX() const{ return {X, X, X}; };
	constexpr Vec3<T> YYY() const{ return {Y, Y, Y}; };
	
	constexpr Vec3<T> YXX() const{ return {Y, X, X}; };
	constexpr Vec3<T> XYX() const{ return {X, Y, X}; };
	constexpr Vec3<T> XXY() const{ return {X, X, Y}; };
	
	constexpr Vec3<T> XYZ() const{ return {X, Y, Z}; };
	constexpr Vec3<T> ZYX() const{ return {Z, Y, X}; };
	constexpr Vec3<T> XZY() const{ return {X, Z, Y}; };
	constexpr Vec3<T> YZX() const{ return {Y, Z, X}; };
	constexpr Vec3<T> YXZ() const{ return {Y, X, Z}; };
	constexpr Vec3<T> ZXY() const{ return {Z, X, Y}; };
};

template<typename T>
float Distance(Vec3<T> a, Vec3<T> b)
{
	return (a - b).getLength();
};

template<typename T>
bool InRange(Vec3<T> a, Vec3<T> b, float range)
{
	return (a - b).sqLength() < (range * range);
};

#define def_operator(OPER)\
template<typename T, typename P> constexpr auto operator OPER(const Vec3<T>& vec, const Vec3<P>& val) -> Vec3<decltype(vec.X OPER val.X)> { return {vec.X OPER val.X, vec.Y OPER val.Y, vec.Z OPER val.Z}; }\
template<typename T, typename P> constexpr auto operator OPER(const Vec3<T>& vec, const P& val) -> Vec3<decltype(vec.X OPER val)> { return {vec.X OPER val, vec.Y OPER val, vec.Y OPER val}; }\
template<typename T, typename P> constexpr auto operator OPER(const P& val, const Vec3<T>& vec) -> Vec3<decltype(vec.X OPER val)> { return {vec.X OPER val, vec.Y OPER val, vec.Y OPER val}; }
def_operator(+);
def_operator(-);
def_operator(/);
def_operator(*);
def_operator(%);
#undef def_operator

#define def_assign_operator(OPER)\
template<typename T, typename P> Vec3<T>& operator OPER(Vec3<T>& vec, const Vec3<P>& val) { vec.X OPER val.X; vec.Y OPER val.Y; vec.Z OPER val.Z; return vec; };\
template<typename T, typename P> Vec3<T>& operator OPER(Vec3<T>& vec, const P& val) { vec.X OPER val; vec.Y OPER val; vec.Z OPER val; return vec; };
def_assign_operator(+=);
def_assign_operator(-=);
def_assign_operator(*=);
def_assign_operator(/=);
def_assign_operator(%=);
#undef def_assign_operator

//! @relates Vec3
//! @{
using Vec3F = Vec3<float>;
using Vec3I = Vec3<int>;
using Vec3U = Vec3<unsigned>;
//! @}

template<typename T> constexpr
Vec3<T> Reorder(const Vec3<T>& vec, const Vec3I& elementOrder)
{
	return { vec[elementOrder[0]], vec[elementOrder[1]], vec[elementOrder[2]] };
};

static constexpr Vec3I XYZ = Vec3I(0, 1, 2);
static constexpr Vec3I ZXY = Vec3I(2, 0, 1);
static constexpr Vec3I YZX = Vec3I(1, 2, 0);
static constexpr Vec3I ZYX = Vec3I(2, 1, 0);
static constexpr Vec3I XZY = Vec3I(0, 2, 1);
static constexpr Vec3I YXZ = Vec3I(1, 0, 2);

#include "Vec3_Templates.hpp"
