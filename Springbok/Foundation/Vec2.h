// Copyright (C) 2013-2015 Manuel Riecke <api.beast@gmail.com>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

//~ ### Vec2
//~ *Dependencies: None except for the C++11 keyword "constexpr".*
//~
//~ A two dimensional vector with overloaded operators for easy vector arithmetics.
//~ TODO: This class requires usage examples as the header itself is not very useful.
template<typename T>
struct Vec2
{
	//~ #### Members
	T X;
	T Y;
	//~!

	//~ #### Constructors
	constexpr Vec2()           : X(   ), Y(   ) {};
	constexpr Vec2(T val)      : X(val), Y(val) {};
	constexpr Vec2(T vx, T vy) : X( vx), Y( vy) {};
	//~!
	
	template<typename P>
	constexpr Vec2(const Vec2<P>& other) : X(other.X), Y(other.Y) {};
	
	constexpr bool operator==(Vec2<T> other) const { return X == other.X && Y == other.Y; };
	constexpr bool operator!=(Vec2<T> other) const { return X != other.X || Y != other.Y; };
	constexpr explicit operator bool()       const { return X && Y; };
	constexpr Vec2<T>  operator-() const;
	T& operator[](int i){ return i ? Y : X; };
	
	//~ #### Functions
	float length() const; // Euclidean distance to {0, 0}
	constexpr Vec2<float> normalized() const; // Returns a vector whose length equals one, pointing in the same direction as this one.
	
	constexpr T          sum() const;
	constexpr float sqLength() const; // Manhattan distance to {0, 0}, does not require calculating the square root.

	constexpr float dot(Vec2<T> other) const;
	constexpr Vec2<T> rot90() const;
	
	constexpr Vec2<T> lowerBound(Vec2<T> other) const;
	constexpr Vec2<T> upperBound(Vec2<T> other) const;
	constexpr bool    isInBounds(Vec2<T> lower, Vec2<T> upper) const;
};

using Vec2F = Vec2<float>;
using Vec2I = Vec2<int>;
using Vec2U = Vec2<unsigned>;
using Vec2C = Vec2<unsigned char>;

#define def_operator(OPER)\
template<typename T, typename P> constexpr auto operator OPER(const Vec2<T>& vec, const Vec2<P>& val) -> Vec2<decltype(vec.X OPER val.X)> { return {vec.X OPER val.X, vec.Y OPER val.Y}; }\
template<typename T, typename P> constexpr auto operator OPER(const Vec2<T>& vec, const P& val) -> Vec2<decltype(vec.X OPER val)> { return {vec.X OPER val, vec.Y OPER val}; }\
template<typename T, typename P> constexpr auto operator OPER(const P& val, const Vec2<T>& vec) -> Vec2<decltype(vec.X OPER val)> { return {vec.X OPER val, vec.Y OPER val}; }
def_operator(+);
def_operator(-);
def_operator(/);
def_operator(*);
def_operator(%);
#undef def_operator

#define def_assign_operator(OPER)\
template<typename T, typename P> Vec2<T>& operator OPER(Vec2<T>& vec, const Vec2<P>& val) { vec.X OPER val.X; vec.Y OPER val.Y; return vec; };\
template<typename T, typename P> Vec2<T>& operator OPER(Vec2<T>& vec, const P& val) { vec.X OPER val; vec.Y OPER val; return vec; };
def_assign_operator(+=);
def_assign_operator(-=);
def_assign_operator(*=);
def_assign_operator(/=);
def_assign_operator(%=);
#undef def_assign_operator

#include "Vec2_Templates.hpp"