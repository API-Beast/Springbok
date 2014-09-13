// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#include <Springbok/Foundation/PointerGuard.h>
#include <Springbok/Platform/FileSystem.h>
#include "ResourceManager.h"

using namespace std;

ResourceManager* ResourceManager::gInstance = nullptr;

ResourceManager* ResourceManager::GetInstance()
{
	// Solution for Bug #14
	// Order of destruction is dependent from order of construction
	// So we need to construct PointerGuard on the first call to GetInstance
	// Not before
	ObjectData::ObjectDataList(); // Always initialize ObjectData before ResourceManager
	static PointerGuard<ResourceManager> guard(&ResourceManager::gInstance);
	
	if(gInstance == nullptr)
		gInstance = new ResourceManager;
	return gInstance;
}

std::string ResourceManager::findPrimaryResourcePath(const vector< string >& paths)
{
	PrimaryResourcePath = ".";
	for(const std::string& path : paths)
	{
		if(FileSystem::Info(path).IsFolder)
		{
			PrimaryResourcePath = path;
			break;
		}
	}
	PrintedResourceSearchPath = false;
	return PrimaryResourcePath;
}

void ResourceManager::addModPath(const string& path)
{
	ModPaths.push_back(path);
	PrintedResourceSearchPath = false;
}

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{
	for(auto pair : Resources)
		pair.second.Pointer.destroy();
}

std::string ResourceManager::getPath(const std::string& path)
{
	for(const std::string& modpath : ModPaths)
	{
		std::string filepath = modpath + "/" + path;
		if(FileSystem::Info(path).IsFile)
			return filepath;
	}
	return PrimaryResourcePath + "/" + path;
}
