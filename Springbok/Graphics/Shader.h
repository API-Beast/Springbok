//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "GLES2.h"
#include <string>

struct Shader
{
	enum ShaderType
	{
		Vertex = GL_VERTEX_SHADER,
		Fragment = GL_FRAGMENT_SHADER
	};
	
	GLuint Handle = 0;
	ShaderType Type;
	std::string Path;
	
	Shader(std::string path, ShaderType type);
};

struct ShaderProgram
{
	Shader VertexShader;
	Shader FragmentShader;
	
	ShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
};

extern Shader gDefaultVertexShader;
extern Shader gDefaultFragmentShader;
extern ShaderProgram gDefaultShader;