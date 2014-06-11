// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <Springbok/Types.hpp>
#include <vector>
#include <string>

class InputDevice
{
public:
	virtual bool isKeyboard() const;
	virtual bool isGamepad() const;
	virtual bool isMouse() const;
	
	virtual const char* id() const;
	
	virtual int   numberOfAxes() const;
	virtual float axisState(int index = 0) const;
	
	virtual int   numberOfCursors() const;
	virtual Vec2F cursorPosition(int index = 0) const;
	
	virtual int   numberOfScrollWheels() const;
	virtual Vec2F scrollWheelState(int index = 0) const;
	virtual void  setScrollWheelState(Vec2F value, int index = 0);
	
	virtual std::string buttonName(int index) const;
	
public:
	int CurrentlyPressedKeys[10];
	void registerKeyPress(int key);
	void registerKeyRelease(int key);
	
	virtual int   numberOfKeys() const;
	virtual bool  isKeyPressed(int index = 0) const;
	virtual bool  isKeyPressed(const std::string& str) const;
	virtual bool  anyKeyPressed() const;
};
