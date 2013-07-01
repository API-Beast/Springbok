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

ButtonSpec::~ButtonSpec()
{
	delete Alternative;
}