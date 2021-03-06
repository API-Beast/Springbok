//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "Vec3.h"

template<typename T>
struct Vec4
{
public:
	union
	{
		T Val[4];
		struct
		{
			T X;
			T Y;
			T Z;
			T W;
		};
		struct
		{
			T R;
			T G;
			T B;
			T A;
		};
		struct
		{
			Vec2<T> XY;
			Vec2<T> ZW;
		};
		struct
		{
			T _padding_A_;
			Vec2<T> YZ;
		};
		struct
		{
			T _padding_B_;
			Vec3<T> YZW;
		};
		Vec3<T> XYZ;
	};
	
	constexpr Vec4() : X(), Y(), Z(), W(1) {};
	template<typename P>
	constexpr Vec4(const P& val) : X(val), Y(val), Z(val), W(val) {};
	template<typename P>
	constexpr Vec4(const Vec3<P>& other, const P& val = 1) : X(other.X), Y(other.Y), Z(other.Z), W(val) {};
	template<typename P>
	constexpr Vec4(const Vec4<P>& other) : X(other.X), Y(other.Y), Z(other.Z), W(other.W) {};
	template<typename P1, typename P2, typename P3>
	constexpr Vec4(const P1& vx, const P2& vy, const P3& vz) : X(vx), Y(vy), Z(vz), W(1) {};
	template<typename P1, typename P2, typename P3, typename P4>
	constexpr Vec4(const P1& vx, const P2& vy, const P3& vz, const P4& vw) : X(vx), Y(vy), Z(vz), W(vw) {};
	
	T& operator[](int x);
	constexpr const T& operator[](int x) const;
	
	constexpr T sortingValue(){ return (X + Y * 100 + Z * 1000 + W * 10000); };
	
	template<typename P> constexpr bool operator==(const Vec4<P>& other){ return X == other.X && Y == other.Y && Z == other.Z && W == other.W;  };
	template<typename P> constexpr bool operator>(const Vec4<P>& other){ return sortingValue() > other.sortingValue();  };
	template<typename P> constexpr bool operator<(const Vec4<P>& other){ return sortingValue() < other.sortingValue();  };
	
	template<typename P> constexpr bool operator!=(const Vec4<P>& other){ return !operator==(other);  };
	template<typename P> constexpr bool operator>=(const Vec4<P>& other){ return operator>(other) || operator==(other);  };
	template<typename P> constexpr bool operator<=(const Vec4<P>& other){ return operator<(other) || operator==(other);  };
	
	constexpr Vec4<T> operator-() const; //!< Returns the opposite of this vector. Equals Vec2(-X, -Y).
	
	constexpr T                  sum() const; //!< Take the sum of the components, also called manhattan length.
	constexpr float         sqLength() const;
	constexpr float           length() const; //!< Returns the \c length of this vector. This is the distance to Vec4(0, 0, 0).
	constexpr Vec4<float> normalized() const; //!< Returns the normalized version of \c this. A normalized vector (also called unit vector) has a length of 1 or 0.
	
	Vec4<T> lowerBound(Vec4<T> other) const;
	Vec4<T> upperBound(Vec4<T> other) const;
	
	constexpr bool isNull() const;
};

template<typename T>
float Distance(Vec4<T> a, Vec4<T> b)
{
	return (a - b).length();
};

template<typename T>
bool InRange(Vec4<T> a, Vec4<T> b, float range)
{
	return (a - b).sqLength() < (range * range);
};

#define def_operator(OPER)\
template<typename T, typename P> constexpr auto operator OPER(const Vec4<T>& vec, const Vec4<P>& val) -> Vec4<decltype(vec[0] OPER val[0])> { return {vec[0] OPER val[0], vec[1] OPER val[1], vec[2] OPER val[2], vec[3] OPER val[3]}; }\
template<typename T, typename P> constexpr auto operator OPER(const Vec4<T>& vec, const P& val) -> Vec4<decltype(vec[0] OPER val)> { return {vec[0] OPER val, vec[1] OPER val, vec[2] OPER val, vec[3] OPER val}; }\
template<typename T, typename P> constexpr auto operator OPER(const P& val, const Vec4<T>& vec) -> Vec4<decltype(vec[0] OPER val)> { return {vec[0] OPER val, vec[1] OPER val, vec[2] OPER val, vec[3] OPER val}; }
def_operator(+);
def_operator(-);
def_operator(/);
def_operator(*);
def_operator(%);
#undef def_operator

#define def_assign_operator(OPER)\
template<typename T, typename P> Vec4<T>& operator OPER(Vec4<T>& vec, const Vec4<P>& val) { vec[0] OPER val[0]; vec[1] OPER val[1]; vec[2] OPER val[2]; vec[3] OPER val[3]; return vec; };\
template<typename T, typename P> Vec4<T>& operator OPER(Vec4<T>& vec, const P& val) { vec[0] OPER val; vec[1] OPER val; vec[2] OPER val; vec[3] OPER val; return vec; };
def_assign_operator(+=);
def_assign_operator(-=);
def_assign_operator(*=);
def_assign_operator(/=);
def_assign_operator(%=);
#undef def_assign_operator

//~ == Typedefs
using Vec4F = Vec4<float>;
using Vec4I = Vec4<int>;
using Vec4U = Vec4<unsigned>;
using Vec4C = Vec4<unsigned char>;
//~!

namespace Colors
{
	static constexpr Vec3F White = Vec3F(1, 1, 1);
	static constexpr Vec3F Black = Vec3F(0, 0, 0);
	
	static constexpr Vec3F Red   = Vec3F(1, 0, 0);
	static constexpr Vec3F Green = Vec3F(0, 1, 0);
	static constexpr Vec3F Blue  = Vec3F(0, 0, 1);
	
	static constexpr Vec4F Transparent = Vec4F(White, 0.0f);
	static constexpr Vec4F Opaque      = Vec4F(White, 1.0f);
};

#include "Vec4_Templates.hpp"
