//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include <Springbok/Graphics/Core/GLES2.h>
#include <Springbok/Utils/Functions.h>
#include <GLFW/glfw3.h>
#include "../GameSurface.h"
#include "WindowUserData.h"

struct GameSurfaceData
{
	GLFWwindow* Window;
	Vec2I WindowSize = 0;
	WindowUserData* DataPointer;
};

namespace
{
	void windowSizeCallback(GLFWwindow* window, int width, int height)
	{
		GameSurfaceData* d = ((WindowUserData*)glfwGetWindowUserPointer(window))->gsd;
		d->WindowSize = {width, height};
		glViewport(0, 0, width, height);
	};
};

GameSurface::GameSurface(const std::string& title, int flags, Vec2U sizeHint, int antiAlias)
{
	d = new GameSurfaceData;
	
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_SAMPLES, antiAlias);
	
	if(flags & Windowed)
	{
		glfwWindowHint(GLFW_RESIZABLE, true);
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
	
	d->DataPointer = new WindowUserData;
	d->DataPointer->gsd = d;
	glfwSetWindowUserPointer(d->Window, d->DataPointer);
	
	glfwSetWindowSizeCallback(d->Window, &windowSizeCallback);
	
	if(flags & NoVSync) glfwSwapInterval(0);
	else glfwSwapInterval(1);
	
	if(!LoadOpenGLFunctions(this))
		DebugLog("Loading OpenGL functions failed.");
}

GameSurface::~GameSurface()
{
	glfwDestroyWindow(d->Window);
	glfwTerminate();
	delete d->DataPointer;
	delete d;
}

void GameSurface::switchBuffers()
{
	glfwPollEvents();
	glfwSwapBuffers(d->Window);
	glfwGetWindowSize(d->Window, &(d->WindowSize.X), &(d->WindowSize.Y));
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