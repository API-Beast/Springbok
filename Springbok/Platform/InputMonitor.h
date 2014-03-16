// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once
#include "ButtonPressEvent.h"
#include <vector>

class GameSurface;
class InputMonitorData;
class InputDevice;
class ButtonPressEvent;
class InputMonitor
{
public:
	InputMonitor(GameSurface* surface);
	~InputMonitor();
	/*int numberOfDevices();
	InputDevice* deviceByIndex(int index);*/
	std::vector<InputDevice*> getDevices() const;
	InputDevice* getPrimaryPointerDevice() const;
	
	std::vector<ButtonPressEvent>  poll();
private:
	InputMonitorData* d;
};