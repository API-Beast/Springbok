#include <GLFW/glfw3.h>
#include "../GameSurface.h"

struct GameSurfaceData
{
	GLFWwindow* Window;
};

GameSurface::GameSurface(const std::string& title, int flags, Vec2U sizeHint)
{
	d = new GameSurfaceData;
	
	glfwInit();
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
	
	int x, y;
	glfwGetWindowSize(d->Window, &x, &y);
	glLoadIdentity();
	glOrtho(0, x, y, 0, 2.0, -2.0);
}

GameSurface::~GameSurface()
{
	glfwDestroyWindow(d->Window);
	glfwTerminate();
	delete d;
}

void GameSurface::switchBuffers()
{
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

Vec2I GameSurface::getSize() const
{
	int x, y;
	glfwGetWindowSize(d->Window, &x, &y);
	return Vec2I(x, y);
}

void* GameSurface::getWindowHandle() const
{
	return d->Window;
}
 