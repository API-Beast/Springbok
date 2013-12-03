// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

template<class A, class B>
struct LogicAnd
{
	LogicAnd(const A& _a, const B& _b) : a(_a), b(_b){};
	template<class... C>
	bool operator()(C... args) const { return a(args...) && b(args...); };
	template<class C>
	bool operator==(const C& arg) const { return (*this)(arg); };
	A a;
	B b;
};

template<class A, class B>
struct LogicOr
{
	LogicOr(const A& _a, const B& _b) : a(_a), b(_b){};
	template<class... C>
	bool operator()(C... args) const { return a(args...) || b(args...); };
	template<class C>
	bool operator==(const C& arg) const { return (*this)(arg); };
	A a;
	B b;
};

template<class T>
struct LogicEqual
{
	LogicEqual(const T& _arg) : arg(_arg){};
	template<class C>
	bool operator()(const C& val) const { return val == arg; };
	template<class C>
	bool operator==(const C& arg) const { return (*this)(arg); };
	T arg;
};

template<class T>
struct LogicNot
{
	LogicNot(const T& _arg) : arg(_arg){};
	template<class... C>
	bool operator()(C... val) const{ return arg(val...); };
	template<class C>
	bool operator==(const C& arg) const{ return (*this)(arg); };
	T arg;
};

template<class T>
struct LogicInSet
{
	LogicInSet(const T& _arg) : arg(_arg){};
	template<class C>
	bool operator()(const C& val) const
	{ 
		for(auto& a : arg)
			if(val == a) return true;
		return false;
	};
	template<class C>
	bool operator==(const C& arg) const { return (*this)(arg); };
	T arg;
};

template<class A, class B>
bool LogicCompare(const A& a, const B& b)
{
	return a == b;
}

template<class A>
bool LogicCompare(const std::initializer_list<A>& a, const A& b)
{
	for(auto val : a) if(b == val) return true;
	return false;
}