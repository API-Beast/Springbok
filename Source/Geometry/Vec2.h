// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <Springbok/Math/Radian.h>

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
	/** @property T X; */
	/** @property T Y; */
  
  Vec2() : X(), Y() {};
  template<typename P> Vec2(P val) : X(val), Y(val) {};
  template<typename P> Vec2(Vec2<P> other) : X(other.X), Y(other.Y) {};
  template<typename P1, typename P2> Vec2(P1 vx, P2 vy) : X(vx), Y(vy) {};
	
  T& operator[](int x);
  constexpr Vec2<T> operator-() const;
	constexpr operator bool() const;
	
	constexpr float getLength() const;
	constexpr Radian getAngle(Vec2<T> up=Vec2<T>(0, -1.f)) const;
	Vec2<T> normalized() const;
	Vec2<T> rotated(Radian angle, Vec2<T> up=Vec2<T>(0, -1.f)) const;
	constexpr float dot(Vec2<T> other) const;
	Vec2<T> projected(Vec2<T> line) const;
	float projectAxis(Vec2<T> axis) const;
	
//! @cond
#define def_operator(OPER)\
  template<typename P> constexpr Vec2<T> operator OPER(P val) const { return Vec2<T>( X OPER val, Y OPER val); };\
  template<typename P> constexpr auto operator OPER(const Vec2<P>& val) const -> Vec2<decltype(X OPER val.X)> { return Vec2<T>( X OPER val.X, Y OPER val.Y); }
  def_operator(+);
  def_operator(-);
  def_operator(/);
  def_operator(*);
  def_operator(%);
  
#define def_assign_operator(OPER)\
  template<typename P> Vec2<T>& operator OPER(P val) { X OPER val; Y OPER val; return *this; };\
  template<typename P> Vec2<T>& operator OPER(const Vec2<P>& val) { X OPER val.X; Y OPER val.Y; return *this;}
  def_assign_operator(+=);
  def_assign_operator(-=);
  def_assign_operator(*=);
  def_assign_operator(/=);
  def_assign_operator(%=);
	
#define def_comp_operator(OPER)\
  template<typename P> constexpr bool operator OPER(P val) const { return getLength() OPER val; };\
  template<typename P> constexpr bool operator OPER(const Vec2<P>& val) const { return getLength() OPER val.getLength(); }
  def_comp_operator(>);
  def_comp_operator(<);
  def_comp_operator(>=);
  def_comp_operator(<=);
//! @endcond
};

//! @relates Vec2
//! @{
using Vec2F = Vec2<float>;
using Vec2I = Vec2<int>;
using Vec2U = Vec2<unsigned>;
//! @}

#include "Vec2_Templates.hpp"