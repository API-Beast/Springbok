//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <string>
#include <vector>

struct Path
{
	Path(const std::string& path, const std::vector<std::string>& searchPaths = gSearchPaths);
	
	operator const std::string&() const{ return ResolvedPath; };
	const char* c_str(){ return ResolvedPath.c_str(); };
	
	std::string   SourcePath;
	std::string ResolvedPath;
	
	static std::vector<std::string> gSearchPaths;
	static void AddSearchPath(const std::string& path);
};