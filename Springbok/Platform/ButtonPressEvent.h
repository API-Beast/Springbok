// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once
#include "InputMonitor.h"

class InputDevice;
class InputMonitor;

enum ButtonType
{
	Any=0,
	Mouse,
	Keyboard,
	Gamepad,
	Misc
};

struct ButtonPressEvent
{
	InputDevice* From;
	ButtonType Type;
	int Button;
};