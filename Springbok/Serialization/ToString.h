//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include <string>
#include <Springbok/Parsing/UTF8.h>
#include <Springbok/Generic/Logic.h>

template<typename T> std::string ToString(T x){ return std::to_string(x); };
inline std::string ToString(float x){ return UTF8::StripRight(std::to_string(x), InSet({'0', '.'})); };
inline std::string ToString(double x){ return UTF8::StripRight(std::to_string(x), InSet({'0', '.'})); };
inline std::string ToString(const std::string& x){ return x; };
// Works for float, int, etc.