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
	constexpr Vec2<T> operator-() const; //!< Returns the opposite of this vector. Equals Vec2(-X, -Y).
	constexpr operator bool()     const; //!< Returns \c true if either X or Y have a value != 0.
	
	constexpr float  getLength() const;  //!< Returns the \c length of this vector. This is the distance to Vec2(0, 0).
	Vec2<T> normalized() const;          //!< Returns the normalized version of \c this. A normalized vector (also called unit vector) has a length of 1 or 0.
	
	constexpr Radian getAngle(Vec2<T> up=Vec2<T>(0, -1.f)) const;     //!< Returns the the angle difference between the direction of \c this and \a up.
	Vec2<T> rotated(Radian angle, Vec2<T> up=Vec2<T>(0, -1.f)) const; //!< Returns \c this rotated by \a angle, whereas the angle is relative to the \a up unit vector.
	
	constexpr float dot(Vec2<T> other) const; //!< Returns the dot product between \c this and \c other.
	
	/*Vec2<T> projected(Vec2<T> line) const; //!< Project this two dimensional vector onto \a axis. @return The projected vector in the 2D space. */// <- Superflucious?
	float projectAxis(Vec2<T> axis) const; //!< Project this two dimensional vector onto \a axis. @return The position of the vector on \a axis.
	
	/** @fn template<typename P> constexpr Vec2<T> operatorOPER(const P& val);
	 *  @memberof Vec2
	 *  Call operator OPER (+, -, * or /) for every component of \c this with \a val as parameter.
	 *  @returns A Vec2<T> with the results of the operation.
	 */
	/** @fn template<typename P> constexpr Vec2<T> operatorOPER(const Vec2<P>& other); 
	 *  @memberof Vec2
	 *  Call operator OPER (+, -, * or /) on every component of \c this with the corresponding component of \a other as parameter.
	 *  @returns A Vec2<T> with the results of the operation.
	 */
	/** @fn template<typename P> constexpr Vec2<T> operatorASSIGN(const P& val);
	 *  @memberof Vec2
	 *  Call assignment operator ASSIGN (+=, -=, *= or /=) for every component of \c this with \a val as parameter.
	 *  @returns Reference to \c *this.
	 */
	/** @fn template<typename P> constexpr Vec2<T> operatorASSIGN(const Vec2<P>& other); 
	 *  @memberof Vec2
	 *  Call assignment operator ASSIGN (+=, -=, *= or /=) on every component of \c this with the corresponding component of \a other as parameter.
	 *  @returns Reference to \c *this.
	 */
	/** @fn template<typename P> constexpr bool operatorCOMPARE(const P& val);
	 *  @memberof Vec2
	 *  Compare the length of \a Vec2<P>(val, val) with the length of \a this using operator COMPARE (>, <, >= or <=).
	 *  @returns The result of the comparison.
	 */
	/** @fn template<typename P> constexpr bool operatorCOMPARE(const Vec2<P>& val);
	 *  @memberof Vec2
	 *  Compare the length of \a val with the length of \a this using operator COMPARE (>, <, >= or <=).
	 *  @returns The result of the comparison.
	 */
	
	//! @cond
	#define def_operator(OPER)\
	template<typename P> constexpr Vec2<T> operator OPER(P val) const { return Vec2<T>( X OPER val, Y OPER val); };\
	template<typename P> constexpr auto operator OPER(const Vec2<P>& val) const -> Vec2<decltype(X OPER val.X)> { return Vec2<T>( X OPER val.X, Y OPER val.Y); }
	def_operator(+);
	def_operator(-);
	def_operator(/);
	def_operator(*);
	def_operator(%);
	#undef def_operator
	
	#define def_assign_operator(OPER)\
	template<typename P> Vec2<T>& operator OPER(const P& val) { X OPER val; Y OPER val; return *this; };\
	template<typename P> Vec2<T>& operator OPER(const Vec2<P>& val) { X OPER val.X; Y OPER val.Y; return *this;}
	def_assign_operator(+=);
	def_assign_operator(-=);
	def_assign_operator(*=);
	def_assign_operator(/=);
	def_assign_operator(%=);
	#undef def_assign_operator
	
	#define def_comp_operator(OPER)\
	template<typename P> constexpr bool operator OPER(const P& val) const { return getLength() OPER val; };\
	template<typename P> constexpr bool operator OPER(const Vec2<P>& val) const { return getLength() OPER val.getLength(); }
	def_comp_operator(>);
	def_comp_operator(<);
	def_comp_operator(>=);
	def_comp_operator(<=);
	#undef def_comp_operator
	//! @endcond
};

//! @relates Vec2
//! @{
using Vec2F = Vec2<float>;
using Vec2I = Vec2<int>;
using Vec2U = Vec2<unsigned>;
//! @}

#include "Vec2_Templates.hpp"