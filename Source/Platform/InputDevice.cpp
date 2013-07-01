// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#include "InputDevice.h"

const char* InputDevice::getIdentifier() const
{
	return "Invalid Device";
}

float InputDevice::getAxisState(int index) const
{
	return 0.0f;
}

bool InputDevice::getButtonState(int index) const
{
	return false;
}

Vec2F InputDevice::getCursorPosition(int index) const
{
	return Vec2F(0.f, 0.f);
}

bool InputDevice::isGamepad() const
{
	return false;
}

bool InputDevice::isKeyboard() const
{
	return false;
}

bool InputDevice::isMouse() const
{
	return false;
}

int InputDevice::numberOfAxes() const
{
	return 0;
}

int InputDevice::numberOfButtons() const
{
	return 0;
}

int InputDevice::numberOfCursors() const
{
	return 0;
}
