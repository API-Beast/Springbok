// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once
#include "Line2.h"

template<typename T>
bool Line2<T>::Line2(const Vec2<T>& A, const Vec2<T>& B)
{
	if(A < B)
	{
		Start = A;
		End   = B;
	}
	else
	{
		Start = B;
		End   = A;
	};
};

template<typename T>
bool Line2<T>::operator==(const Line2<T>& other) const
{
	return other.Start == this->Start && other.End == this->Start;
};

template<typename T>
bool Line2<T>::isIntersecting(const Line2<T>& other) const
{
	const Vec2<T>& A = this->Start;
	const Vec2<T>& B = this->End;
	const Vec2<T>& C = other.Start;
	const Vec2<T>& D = other.End;
	auto isCounterClockWise = [](Vec2<T> A, Vec2<T> B, Vec2<T> C){ return (C.y - A.y) * (B.x - A.x) > (B.y-A.y) * (C.x-A.x); };
	return isCounterClockWise(A, C, D) != isCounterClockWise(B, C, D) &&
				 isCounterClockWise(A, B, C) != isCounterClockWise(A, B, D);
};

template<typename T>
Vec2<T> Line2<T>::direction() const
{
	return End - Start;
};