//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "Logic_Implementation.hpp"

template<typename A, typename B>
_Or<A,B> Or(const A& a, const B& b)
{
	return _Or<A,B>(a, b);
};

template<typename A, typename B>
_And<A,B> And(const A& a, const B& b)
{
	return _And<A,B>(a, b);
};

template<typename A>
_Not<A> Not(const A& a)
{
	return _Not<A>(a);
};

template<typename T>
_InSet<T> InSet(const std::initializer_list<T>& list)
{
	return _InSet<T>(list);
};

template<typename T>
_EqualTo<T> EqualTo(const T& value)
{
	return _EqualTo<T>(value);
};