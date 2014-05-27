// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <Springbok/Types.hpp>
#include <string>

class InputDevice
{
public:
	virtual bool isKeyboard() const;
	virtual bool isGamepad() const;
	virtual bool isMouse() const;
	
	virtual const char* getIdentifier() const;
	
	virtual int   numberOfAxes() const;
	virtual float getAxisState(int index = 0) const;
	
	virtual int   numberOfButtons() const;
	virtual bool  getButtonState(int index = 0) const;
	virtual bool  anyButtonPressed() const;
	
	virtual int   numberOfCursors() const;
	virtual Vec2F getCursorPosition(int index = 0) const;
	
	virtual int   numberOfScrollWheels() const;
	virtual Vec2F getScrollWheelState(int index = 0) const;
	virtual void  setScrollWheelState(Vec2F value, int index = 0);
	
	virtual std::string getButtonName(int index) const;
};