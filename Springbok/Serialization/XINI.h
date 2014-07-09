//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "ValueTree.h"

#include <string>
#include <ostream>

ValueTree LoadXINI(const std::string& path);
void WriteXINI(const ValueTree& tree, std::ostream& out, int intendation = 0);