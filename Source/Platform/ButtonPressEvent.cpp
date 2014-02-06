// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#include "ButtonPressEvent.h"
#include "InputDevice.h"

bool ButtonSpec::matches(const ButtonPressEvent& event)
{
	bool retVal = true;
	if(From)
		retVal = retVal && (event.From == From);
	if(Type)
		retVal = retVal && (event.Type == Type);
	if(Button != -1)
		retVal = retVal && (event.Button == Button);
	if(ComboButton != -1)
		retVal = retVal && event.From->getButtonState(ComboButton);
	
	if(retVal == false)
		if(Alternative)
			retVal = Alternative->matches(event);
		
	return retVal;
}

bool ButtonSpec::isPressed(InputMonitor* monitor)
{
	bool retVal;
	for(InputDevice* device : monitor->getDevices())
	{
		if(device->anyButtonPressed())
		{
			retVal = true;
			if(From)
				retVal = retVal && (device == From);
			if(Type)
			{
				if(Type == Mouse)
					retVal = retVal && device->isMouse();
				else if(Type == Keyboard)
					retVal = retVal && device->isKeyboard();
				else if(Type == Gamepad)
					retVal = retVal && device->isGamepad();
			}
			if(Button != -1)
				retVal = retVal && device->getButtonState(Button);
			if(ComboButton != -1)
				retVal = retVal && device->getButtonState(ComboButton);
		}
		else retVal = false;
		
		if(retVal)
			break;
	}
	
	if(retVal == false)
		if(Alternative)
			retVal = Alternative->isPressed(monitor);
		
	return retVal;
}

ButtonSpec::~ButtonSpec()
{
	delete Alternative;
}