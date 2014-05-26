//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <string>
#include <fstream>

inline std::string ReadFileFull(const std::string& path)
{
	std::ifstream file(path, std::ios::binary);
	std::string fileContent((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
	return fileContent;
}