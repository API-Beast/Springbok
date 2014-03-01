#include "HelloWorld.h"
#include <Source/Resources/ResourceManager.h>
#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

HelloWorld* game;

void one_iter()
{
	game->render();
}

int main()
{
	ResourceManager::GetInstance()->findPrimaryResourcePath({"./Assets"});
	game = new HelloWorld();
	game->execute();
	
#ifdef EMSCRIPTEN
	emscripten_set_main_loop(one_iter, 60, 1);
#else
	while(game->isRunning())
	{
		game->render();
	}
#endif
	delete game;
}
