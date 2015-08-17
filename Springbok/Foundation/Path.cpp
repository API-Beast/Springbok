//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "Path.h"
#include <Springbok/Platform/FileSystem.h>

std::vector<std::string> Path::gSearchPaths;

Path::Path(const std::string& path, const std::vector< std::string >& searchPaths)
{
	for(const std::string& searchpath : searchPaths)
	{
		std::string filepath = searchpath + "/" + path;
		if(FileSystem::Info(filepath).IsFile)
		{
			ResolvedPath = filepath;
			// Note this is overwriting the old results, e.g. later entries in the Search Path have higher priority.
		}
	}
}

void Path::AddSearchPath(const std::string& path)
{
	gSearchPaths.push_back(path);
}
