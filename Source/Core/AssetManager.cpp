// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#include "AssetManager.h"
#include <iostream>

using namespace std;


AssetManager* AssetManager::gInstance = nullptr;

AssetManager* AssetManager::GetInstance()
{
	if(gInstance == nullptr)
		gInstance = new AssetManager;
	return gInstance;
}

namespace
{
	#include <sys/stat.h>

	bool FolderExists(const std::string& path)
	{
		struct stat fileInfo;
		int failed;
		failed = stat(path.c_str(), &fileInfo);
		return !failed && fileInfo.st_mode & S_IFDIR;
	}

	bool FileExists(const std::string& path)
	{
		struct stat fileInfo;
		int failed;
		failed = stat(path.c_str(), &fileInfo);
		return !failed && !fileInfo.st_mode & S_IFDIR;
	}
}

void AssetManager::findPrimaryAssetPath(const vector< string >& paths)
{
	for(const std::string& path : paths)
	{
		if(FolderExists(path))
		{
			PrimaryAssetPath = path;
			break;
		}
	}
	cout << "Loading assets from " << PrimaryAssetPath << endl;
}

void AssetManager::addModPath(const string& path)
{
	ModPaths.push_back(path);
}

void AssetManager::postLoadAll()
{

}

AssetManager::AssetManager() : Textures(this), Sounds(this){}

std::string AssetManager::getPath(const std::string& path)
{
	for(const std::string& modpath : ModPaths)
	{
		std::string filepath = modpath + "/" + path;
		if(FileExists(filepath))
			return filepath;
	}
	return PrimaryAssetPath + "/" + path;
}
