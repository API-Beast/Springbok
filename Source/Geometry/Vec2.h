// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <ostream>

template<typename T>
struct Vec2
{
public:
	//! @cond
	union
	{
		T Val[2];
		struct
		{
			T X;
			T Y;
		};
	};
	//! @endcond
	/** @var T X;
	 * @memberof Vec2
	 * @brief The X component of this Vec2. */
	/** @var T Y;
	 * @memberof Vec2
	 * @brief The Y component of this Vec2. */
	
	constexpr Vec2() : X(), Y() {};
	template<typename P>
	constexpr Vec2(const P& val) : X(val), Y(val) {};
	template<typename P>
	constexpr Vec2(const Vec2<P>& other) : X(other.X), Y(other.Y) {};
	template<typename P1, typename P2>
	constexpr Vec2(const P1& vx, const P2& vy) : X(vx), Y(vy) {};
	
	T& operator[](int x);
	const T& operator[](int x) const;
	template<typename P> constexpr bool operator==(const Vec2<P>& other){ return X == other.X && Y == other.Y;  };
	template<typename P> constexpr bool operator>(const Vec2<P>& other){ return X > other.X || Y > other.Y;  };
	template<typename P> constexpr bool operator<(const Vec2<P>& other){ return X < other.X && Y < other.Y;  };
	constexpr Vec2<T> operator-() const; //!< Returns the opposite of this vector. Equals Vec2(-X, -Y).
	
	constexpr float  getLength() const;  //!< Returns the \c length of this vector. This is the distance to Vec2(0, 0).
	Vec2<T> normalized() const;          //!< Returns the normalized version of \c this. A normalized vector (also called unit vector) has a length of 1 or 0.

	constexpr float dot(Vec2<T> other) const; //!< Returns the dot product between \c this and \c other.
	
	/*Vec2<T> projected(Vec2<T> line) const; //!< Project this two dimensional vector onto \a axis. @return The projected vector in the 2D space. */// <- Superflucious?
	float projectAxis(Vec2<T> axis) const; //!< Project this two dimensional vector onto \a axis. @return The position of the vector on \a axis.
	
	constexpr bool isNull() const;
};

#define def_operator(OPER)\
template<typename T, typename P> constexpr auto operator OPER(const Vec2<T>& vec, const Vec2<P>& val) -> Vec2<decltype(vec.X OPER val.X)> { return Vec2<T>( vec.X OPER val.X, vec.Y OPER val.Y); }\
template<typename T, typename P> constexpr auto operator OPER(const Vec2<T>& vec, const P& val) -> Vec2<decltype(vec.X OPER val)> { return Vec2<T>( vec.X OPER val, vec.Y OPER val); }\
template<typename T, typename P> constexpr auto operator OPER(const P& val, const Vec2<T>& vec) -> Vec2<decltype(vec.X OPER val)> { return Vec2<T>( vec.X OPER val, vec.Y OPER val); }
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

//! @relates Vec2
//! @{
using Vec2F = Vec2<float>;
using Vec2I = Vec2<int>;
using Vec2U = Vec2<unsigned>;
//! @}

template<typename T>
std::ostream& operator<< (std::ostream& stream, const Vec2<T>& obj)
{
	return stream << "(" << obj.X << "," << obj.Y << ")";
}

#include "Vec2_Templates.hpp"