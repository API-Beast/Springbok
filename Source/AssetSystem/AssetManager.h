// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <vector>
#include <map>
#include <string>

#include <Graphics/Texture.h>
#include <Audio/SoundSample.h>

class AssetManager;

//! @cond
template<typename T>
class AssetList
{
public:
	AssetList(AssetManager* parent){ mParent = parent; };
	T*& operator[](const std::string& filename);
private:
	std::map<std::string, T*> mMap;
	AssetManager* mParent;
};
//! @endcond

//! @ingroup AssetManager
class AssetManager
{
public:
	// TODO Replace with more flexible version, so that you don't need to include SoundSample.h or Texture.h if not necessary.
	AssetList<Texture>     Textures;
	AssetList<SoundSample> Sounds;
	
	std::string PrimaryAssetPath;
	std::vector<std::string> ModPaths;
//!@name Static
///@{
public:
	static AssetManager* gInstance;
	static AssetManager* GetInstance();
///@}
public:
	AssetManager();
	std::string getPath(const std::string& path);
	void findPrimaryAssetPath(const std::vector<std::string>& paths);
	void addModPath(const std::string& path);
	void postLoadAll();
};

#include "AssetManager_Template.hpp"