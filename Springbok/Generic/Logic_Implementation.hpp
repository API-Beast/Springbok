//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <initializer_list>

template<class A, class B>
struct _Or
{
	const A& a;
	const B& b;
	constexpr _Or(const A& _a, const B& _b) : a(_a), b(_b){};
	template<typename... T>
	auto operator()(T... args) const -> decltype(a(args...) || b(args...)) { return a(args...) || b(args...); };
};

template<class A, class B>
struct _And
{
	const A& a;
	const B& b;
	constexpr _And(const A& _a, const B& _b) : a(_a), b(_b){};
	template<typename... T>
	auto operator()(T... args) const -> decltype(a(args...) && b(args...)) { return a(args...) && b(args...); };
};

template<class T>
struct _InSet
{
	const std::initializer_list<T>& Set;
	constexpr _InSet(const std::initializer_list<T>& set) : Set(set){};
	bool operator()(const T& arg) const
	{ 
		for(const T& val : Set)
			if(arg == val)
				return true;
		return false;
	};
};

template<class T>
struct _EqualTo
{
	const T& Value;
	constexpr _EqualTo(const T& value) : Value(value){};
	constexpr bool operator()(const T& arg) const
	{
		return Value == arg;
	};
};

template<class A>
struct _Not
{
	const A& a;
	constexpr _Not(const A& _a) : a(_a){};
	template<typename... T>
	auto operator()(T... args) const -> decltype(!a(args...)) { return !a(args...); };
};