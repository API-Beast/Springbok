#include "TopDownShooter.h"
#include <Source/Resources/ResourceManager.h>

int main()
{
	ResourceManager::GetInstance()->findPrimaryResourcePath({"./Assets"});
	TopDownShooter game;
	return game.execute();
}