// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "ResourceManager.h"

#include <typeinfo>

#include <cassert>

template<typename T, class... Args>
ObjectPointer< T > ResourceManager::getResource(const std::string& path, Args... args)
{
	auto resourceIter = Resources.find(path);
	if(resourceIter != Resources.end())
	{
		auto& resource = resourceIter->second;
		if(false) // Should reload?
		{
			resource.Pointer.destroy();
			resource.Pointer.replaceWith(reinterpret_cast<void*>(new T(resource.ResolvedPath, args...)));;
			resource.DataType = typeid(T).hash_code();
		}
		else;
			//assert(typeid(T).hash_code() == resource.DataType);
		
		return reinterpret_pointer_cast<T*>(resource.Pointer);
	}
	else
	{
		auto& resource = Resources[path];
		resource.RequestedPath = path;
		resource.ResolvedPath  = getPath(path);
		resource.Pointer  = new T(resource.ResolvedPath, args...);
		resource.DataType = typeid(T).hash_code();
		return reinterpret_pointer_cast<T*>(resource.Pointer);
	}
};