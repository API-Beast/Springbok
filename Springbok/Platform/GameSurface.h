// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once
#include <string>

#include <Springbok/Foundation/Vec2.h>
#include <Springbok/Graphics/Core/RenderTarget.h>

class GameSurfaceData;

class GameSurface : public RenderTarget
{
public:
	enum WindowFlags
	{
		None = 0,
		Windowed = 1,
		NoVSync = 2
	};
public:
	GameSurface(const std::string& title, int flags = None, Vec2U sizeHint = Vec2U(800, 600), int antiAlias = 0);
	~GameSurface();
	
	void switchBuffers();
	bool closeRequested() const;
	void requestClose();
	
	using GLFunctionPointer = void(*)(void);

	template<typename T>
	T getGLFunction(const char* name)
	{
		return reinterpret_cast<T>(getGLFunction(name));
	};
	GLFunctionPointer getGLFunction(const char* name);
	bool isGLExtSupported(const char* name);
	
	virtual Vec2F size() const;
	virtual void bind();
protected:
	void* getWindowHandle() const;
	friend class InputMonitor;
private:
	GameSurfaceData* d;
};