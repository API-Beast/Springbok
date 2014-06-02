//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <string>
#include <vector>

namespace FileSystem
{	
	std::string   ParentPath(const std::string& path);
	std::string AbsolutePath(const std::string& path);
	std::string RelativePath(const std::string& path, const std::string& relativeTo);
	
	std::vector<std::string> FolderContents(const std::string& dir); 
	
	struct Info
	{
		Info(const std::string& path);
		bool Exists   = false;     // Wheter the file or folder exists.
		bool IsFile   = false;     // Wheter the path is a file.
		bool IsFolder = false;     // Wheter the path is a folder.
		bool IsLink   = false;     // Wheter the path is a symbolic link.
		int  LastModification = 0; // Seconds since last modifiation.
		int  Size = 0;             // Size of the file in Bytes. 0 for Directories.
		std::string Path;          // The path given in the constructor.
		std::string LinkedPath;    // The path linked to or a empty string if "IsLink" is false.
		
		explicit operator bool(){ return Exists; };
	};
};