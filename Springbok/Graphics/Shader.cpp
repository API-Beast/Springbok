//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "Shader.h"
#include "../Utils/Debug.h"

#include <fstream>

namespace
{
	std::string GetShaderLog(GLuint id)
	{
		int infoLogLength;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::string output(infoLogLength, ' ');
		glGetShaderInfoLog(id, infoLogLength, NULL, &output[0]);
		if(!output.empty())
		{
			if(output.back() == '\n') // Brrr I hate that last new line
				output = output.substr(0, output.size() - 1);
		}
		return output;
	}
};

Shader::Shader(Shader::ShaderType type)
{
	Handle = glCreateShader(type);
	Type = type;
}

Shader::Shader(const std::string& path, Shader::ShaderType type)
{
	std::ifstream file(path, std::ios::binary);
	std::streambuf* fileBuffer = file.rdbuf();
	std::string fileContent;
	auto size = fileBuffer->pubseekoff(0, std::ios_base::end);
	fileContent.reserve(size);
	fileBuffer->sgetn(&fileContent[0], size);
	
	Handle = glCreateShader(type);
	Type = type;
}

Shader::~Shader()
{
	glDeleteShader(Handle);
}

void Shader::loadSourceFromBuffer(const std::string& buffer)
{		
	const char* ptr = buffer.data();
	glShaderSource(Handle, 1, &ptr, NULL);
}

bool Shader::compile()
{
	glCompileShader(Handle);
	int success;
	glGetShaderiv(Handle, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		if(Type == Vertex)
			Debug::Write("Vertex shader compilation failed:\n $", GetShaderLog(Handle));
		if(Type == Fragment)
			Debug::Write("Fragment shader compilation failed:\n $", GetShaderLog(Handle));
	}
	return success;
}
