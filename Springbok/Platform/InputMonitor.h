// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "ButtonPressEvent.h"
#include <Springbok/Types.hpp>
#include <vector>
#include <string>

class GameSurface;
class InputMonitorData;
class InputDevice;
class ButtonPressEvent;
class InputMonitor
{
public:
	InputMonitor(GameSurface* surface);
	~InputMonitor();
	
	// Device API
	std::vector<InputDevice*> getDevices() const;
	InputDevice* mouse() const;
	InputDevice* keyboard() const;
	
	// Simplified API for quick prototyping
	bool isKeyPressed(int key);
	bool isKeyPressed(const std::string& key);
	bool isMouseButtonPressed(int button);
	Vec2F mousePosition();
	
	float scrollState();
	void setScrollState(float state);
	
	std::vector<ButtonPressEvent>  poll();
private:
	InputMonitorData* d;
};