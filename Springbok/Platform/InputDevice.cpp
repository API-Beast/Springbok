// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#include "InputDevice.h"

const char* InputDevice::id() const
{
	return "Invalid Device";
}

float InputDevice::axisState(int index) const
{
	return 0.0f;
}

Vec2F InputDevice::cursorPosition(int index) const
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

int InputDevice::numberOfKeys() const
{
	return 0;
}

int InputDevice::numberOfCursors() const
{
	return 0;
}

int InputDevice::numberOfScrollWheels() const
{
	return 0;
}

Vec2F InputDevice::scrollWheelState(int index) const
{
	return 0;
}

void InputDevice::setScrollWheelState(Vec2F value, int index)
{

}


std::string InputDevice::buttonName(int index) const
{
	return std::string(id()) + std::to_string(index);
}

void InputDevice::registerKeyPress(int key)
{
	for(int i = 0; i < 10; ++i)
		if(CurrentlyPressedKeys[i] == -1)
		{
			CurrentlyPressedKeys[i] = key;
			break;
		}
}

void InputDevice::registerKeyRelease(int key)
{
	for(int i = 0; i < 10; ++i)
		if(CurrentlyPressedKeys[i] == key)
			CurrentlyPressedKeys[i] = -1;
}

bool InputDevice::isKeyPressed(int index) const
{
	for(int i = 0; i < 10; ++i)
		if(CurrentlyPressedKeys[i] == index)
			return true;
	return false;
}

bool InputDevice::isKeyPressed(const std::string& str) const
{
	for(int i = 0; i < 10; ++i)
		if(CurrentlyPressedKeys[i] != -1)
			if(buttonName(CurrentlyPressedKeys[i]) == str)
				return true;
	return false;
}

bool InputDevice::anyKeyPressed() const
{
	for(int i = 0; i < 10; ++i)
		if(CurrentlyPressedKeys[i] != -1)
			return true;
	return false;
}
