// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#include <Springbok/Types/PointerGuard.h>
#include <Springbok/Platform/FileInfo.h>
#include "ResourceManager.h"
#include <iostream>

using namespace std;


ResourceManager* ResourceManager::gInstance = nullptr;

// Make sure that gInstance gets deleted when the application gets closed
namespace
{
	PointerGuard<ResourceManager> guard(&ResourceManager::gInstance);
}

ResourceManager* ResourceManager::GetInstance()
{
	if(gInstance == nullptr)
		gInstance = new ResourceManager;
	return gInstance;
}

std::string ResourceManager::findPrimaryResourcePath(const vector< string >& paths)
{
	PrimaryResourcePath = ".";
	for(const std::string& path : paths)
	{
		if(FileInfo(path).Type == FileInfo::Directory)
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
		if(FileInfo(path).Type == FileInfo::File)
			return filepath;
	}
	return PrimaryResourcePath + "/" + path;
}
