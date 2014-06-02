//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "FileSystem.h"

#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstdlib>

FileSystem::Info::Info(const std::string& path)
{
	Path = path;
	
	struct stat fileInfo;
	int failed = stat(path.c_str(), &fileInfo);
	Exists = !failed;
	if(Exists)
	{
		if((fileInfo.st_mode & S_IFDIR) == S_IFDIR)
			IsFolder = true;
		if((fileInfo.st_mode & S_IFREG) == S_IFREG)
			IsFile = true;
		if((fileInfo.st_mode & S_IFLNK) == S_IFLNK)
		{
			IsLink = true;
			char* buffer = new char[fileInfo.st_size + 1];
			readlink(path.c_str(), buffer, fileInfo.st_size + 1);
			buffer[fileInfo.st_size] = '\0';
			LinkedPath = buffer;
		}
		
		LastModification = time(NULL) - fileInfo.st_mtime;
		Size = fileInfo.st_size;
	}
}

std::string FileSystem::ParentPath(const std::string& path)
{
	return path.substr(0, path.find_last_of('/'));
}

std::string FileSystem::AbsolutePath(const std::string& path)
{
	char* rp = realpath(path.c_str(), NULL);
	std::string retVal = rp;
	free(rp);
	return retVal;
}

std::string FileSystem::RelativePath(const std::string& path, const std::string& relativeTo)
{
	std::string absolutePath = AbsolutePath(path);
	std::string relativeToPath = AbsolutePath(relativeTo);
	std::string result;
	// Absolute path starts with relativeToPath, just cut of the known part
	if(absolutePath.compare(0, relativeToPath.length(), relativeToPath) == 0)
	{
		result = absolutePath.substr(relativeToPath.length());
		if(result[0] == '/')
			return result.substr(1);
		return result;
	}
	else
	{
		// TODO
		return absolutePath;
	}
}

std::vector< std::string > FileSystem::FolderContents(const std::string& dir)
{

}
