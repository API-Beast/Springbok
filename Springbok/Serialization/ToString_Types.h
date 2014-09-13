//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "ToString.h"
#include <Springbok/Foundation.hpp>

template<typename T> std::string ToString(Vec2<T> x){ return "(" + ToString(x[0]) + ", " + ToString(x[1]) + ")" ; };
template<typename T> std::string ToString(Vec3<T> x){ return "(" + ToString(x[0]) + ", " + ToString(x[1]) + ", " + ToString(x[2]) + ")" ; };
template<typename T> std::string ToString(Vec4<T> x){ return "(" + ToString(x[0]) + ", " + ToString(x[1]) + ", " + ToString(x[2]) + ", " + ToString(x[3]) + ")" ; };

inline std::string ToString(Angle x){ return ToString(x.toDegree())+"°"; };