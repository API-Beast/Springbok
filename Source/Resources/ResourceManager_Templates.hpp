// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "ResourceManager.h"
#include <Springbok/Utils/Debug.h>

#include <typeinfo>

#include <cassert>

template<typename T>
ObjectPointer< T > ResourceManager::getResource(const std::string& path, bool reload)
{
	auto resourceIter = Resources.find(path);
	if(resourceIter != Resources.end())
	{
		auto& resource = resourceIter->second;
		if(reload)
		{
			resource.Pointer.destroy();
			resource.Pointer.replaceWith(reinterpret_cast<void*>(new T(resource.ResolvedPath)));;
			resource.DataType = typeid(T).hash_code();
		}
		else;
			//assert(typeid(T).hash_code() == resource.DataType);
		
		return reinterpret_pointer_cast<T*>(resource.Pointer);
	}
	else
	{
		std::string fullPath = getPath(path);
		Debug::Write("Loading resource $...",fullPath);
		
		auto& resource = Resources[path];
		resource.RequestedPath = path;
		resource.ResolvedPath  = fullPath;
		resource.Pointer  = new T(resource.ResolvedPath);
		resource.DataType = typeid(T).hash_code();
		return reinterpret_pointer_cast<T*>(resource.Pointer);
	}
};