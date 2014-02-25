#include "HelloWorld.h"
#include <Source/Resources/ResourceManager.h>

int main()
{
	ResourceManager::GetInstance()->findPrimaryResourcePath({"./Assets"});
	HelloWorld game;
	return game.execute();
}