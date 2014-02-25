#include "../GameSurface.h"
#include <Springbok/Utils/Debug.h>

#include <SDL/SDL.h>
#include <GL/gl.h>

struct GameSurfaceData
{
	SDL_Surface* Window;
	Vec2U size;
};

GameSurface::GameSurface(const std::string& title, int flags, Vec2U sizeHint)
{
	d = new GameSurfaceData;

	Debug::Write("Init SDL...");
	int result = SDL_Init(SDL_INIT_VIDEO);
	if(result != 0)
		Debug::Write("Couldn't init SDL: $",SDL_GetError());
	Debug::Write("Open window @ $x$",sizeHint.X,sizeHint.Y);
	d->Window = SDL_SetVideoMode(sizeHint.X, sizeHint.Y, 16, SDL_OPENGL);
	if(!d->Window)
		Debug::Write("Couldn't open window!");
	
	d->size = sizeHint;

	glLoadIdentity();
	glOrtho(0, sizeHint.X, sizeHint.Y, 0, 2.0, -2.0);
}

GameSurface::~GameSurface()
{
	SDL_Quit();
	delete d;
}

void GameSurface::switchBuffers()
{
	SDL_GL_SwapBuffers();
}

bool GameSurface::closeRequested() const
{
	return false;
	//return glfwWindowShouldClose(d->Window);
}

void GameSurface::requestClose()
{
	return;
	//return glfwSetWindowShouldClose(d->Window, true);
}

Vec2I GameSurface::getSize() const
{
	return Vec2I(d->size.X, d->size.Y);
}

void* GameSurface::getWindowHandle() const
{
	return d->Window;
}
 