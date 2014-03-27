// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <Springbok/Geometry/Vec2.h>
#include <string>

class InputDevice
{
public:
	virtual bool isKeyboard() const;
	virtual bool isGamepad() const;
	virtual bool isMouse() const;
	
	virtual const char* getIdentifier() const;
	
	virtual int   numberOfAxes() const;
	virtual float getAxisState(int index) const;
	
	virtual int   numberOfButtons() const;
	virtual bool  getButtonState(int index) const;
	virtual bool  anyButtonPressed() const;
	
	virtual int   numberOfCursors() const;
	virtual Vec2F getCursorPosition(int index) const;
	
	virtual std::string getNameOfButton(int index) const;
};