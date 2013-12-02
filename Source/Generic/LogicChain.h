// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once
#include <initializer_list>
#include <functional>

template<class A, class B> struct LogicAnd;
template<class A, class B> struct LogicOr;
template<class A>          struct LogicEqual;
template<class A>          struct LogicNot;

template<class A, class B> LogicAnd<A,B> _and(const A& a, const B& b){ return LogicAnd<A,B>(a, b); };
template<class A, class B> LogicOr <A,B> _or(const A& a, const B& b){ return LogicOr<A,B>(a, b); };
template<class A>          LogicEqual<A> eq(const A& comp         ){ return LogicEqual<A>(comp); };
template<class A>          LogicNot<A>   neg(const A& a            ){ return LogicNot<A>(a); };

template<class... C>
bool LogicCompare(std::function<bool (C...)> a, C... args)
{
	return a(args...);
}
// Specializations for A being a value (check if equal), A being a function pointer (call function pointer), A being a initializer_list (check if value is in list)

#include "LogicChain_Templates.hpp"