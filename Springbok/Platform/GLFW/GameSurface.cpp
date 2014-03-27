//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include <Springbok/Graphics/GLES2.h>
#include <Springbok/Utils/Debug.h>
#include <GLFW/glfw3.h>
#include "../GameSurface.h"

struct GameSurfaceData
{
	GLFWwindow* Window;
	Vec2I WindowSize = 0;
};

GameSurface::GameSurface(const std::string& title, int flags, Vec2U sizeHint)
{
	d = new GameSurfaceData;
	
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	
	if(flags & Windowed)
	{
		glfwWindowHint(GLFW_RESIZABLE, false);
		glfwWindowHint(GLFW_DECORATED, true);
		d->Window = glfwCreateWindow(sizeHint.X, sizeHint.Y, title.c_str(), NULL, NULL );
	}
	else
	{
		GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* desktopVidMode = glfwGetVideoMode(primaryMonitor);
		glfwWindowHint(GLFW_DECORATED, false);
		d->Window = glfwCreateWindow(desktopVidMode->width, desktopVidMode->height, title.c_str(), primaryMonitor, NULL );
	}
	glfwMakeContextCurrent(d->Window);
	glfwSetInputMode(d->Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	
	if(flags & NoVSync);
	else glfwSwapInterval(1);
	
	if(!LoadOpenGLFunctions(this))
		Debug::Write("Loading OpenGL functions failed.");
}

GameSurface::~GameSurface()
{
	glfwDestroyWindow(d->Window);
	glfwTerminate();
	delete d;
}

void GameSurface::switchBuffers()
{
	glfwPollEvents();
	glfwSwapBuffers(d->Window);
}

bool GameSurface::closeRequested() const
{
	return glfwWindowShouldClose(d->Window);
}

void GameSurface::requestClose()
{
	return glfwSetWindowShouldClose(d->Window, true);
}

void* GameSurface::getWindowHandle() const
{
	return d->Window;
}

GameSurface::GLFunctionPointer GameSurface::getGLFunction(const char* name)
{
	return glfwGetProcAddress(name);
}

bool GameSurface::isGLExtSupported(const char* name)
{
	return glfwExtensionSupported(name);
}

Vec2F GameSurface::size() const
{
	if(d->WindowSize == Vec2I(0))
	{
		int x, y;
		glfwGetWindowSize(d->Window, &(d->WindowSize.X), &(d->WindowSize.Y));
	}
	return d->WindowSize;
}
 
void GameSurface::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}