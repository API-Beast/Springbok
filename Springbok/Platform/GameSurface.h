// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once
#include <string>
#include <Springbok/Geometry/Vec2.h>

class GameSurfaceData;

class GameSurface
{
public:
	enum WindowFlags
	{
		None = 0,
		Windowed = 1,
		NoVSync = 2
	};
public:
	GameSurface(const std::string& title, int flags = None, Vec2U sizeHint = Vec2U(800, 600));
	~GameSurface();
	
	Vec2I getSize() const;
	void switchBuffers();
	bool closeRequested() const;
	void requestClose();
protected:
	void* getWindowHandle() const;
	friend class InputMonitor;
private:
	GameSurfaceData* d;
};