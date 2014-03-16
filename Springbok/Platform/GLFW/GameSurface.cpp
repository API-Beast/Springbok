#include <Springbok/Graphics/GLES2.h>
#include <Springbok/Utils/Debug.h>
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
	
	Debug::Write("Load OpenGL extensions...");
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

GameSurface::GLFunctionPointer GameSurface::getGLFunction(const char* name)
{
	return glfwGetProcAddress(name);
}

bool GameSurface::isGLExtSupported(const char* name)
{
	return glfwExtensionSupported(name);
}
 