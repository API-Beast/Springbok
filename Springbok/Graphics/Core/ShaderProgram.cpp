//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "ShaderProgram.h"
#include <Springbok/Foundation/ResourceManager.h>
#include <Springbok/Foundation/PointerGuard.h>
#include <Springbok/Utils/Functions.h>

namespace
{
	std::string GetShaderProgramLog(GLuint id)
	{
		int infoLogLength;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::string output(infoLogLength, ' ');
		glGetProgramInfoLog(id, infoLogLength, NULL, &output[0]);
		if(!output.empty())
		{
			if(output.back() == '\n') // Brrr I hate that last new line
				output = output.substr(0, output.size() - 1);
		}
		return output;
	}
};

ShaderProgram::ShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
	VertexShader   = ResourceManager::GetInstance()->getResource<Shader>(vertexShaderPath, Shader::Vertex);
	FragmentShader = ResourceManager::GetInstance()->getResource<Shader>(fragmentShaderPath, Shader::Fragment);
}

ShaderProgram::ShaderProgram(const std::string& fragmentShaderPath)
{
	VertexShader   = GetDefaultShader().VertexShader;
	FragmentShader = ResourceManager::GetInstance()->getResource<Shader>(fragmentShaderPath, Shader::Fragment);
}

void ShaderProgram::loadFragmentShader(const std::string& path)
{
	FragmentShader = ResourceManager::GetInstance()->getResource<Shader>(path, Shader::Fragment);
}

void ShaderProgram::loadVertexShader(const std::string& path)
{
	VertexShader   = ResourceManager::GetInstance()->getResource<Shader>(path, Shader::Vertex);
}


void ShaderProgram::deleteShader()
{
	if(glIsProgram(Handle))
	{
		glDeleteProgram(Handle);
		Handle = 0;
	}
}


bool ShaderProgram::link()
{
	if(!Handle)
		Handle = glCreateProgram();
	glAttachShader(Handle, VertexShader   -> Handle);
	glAttachShader(Handle, FragmentShader -> Handle);
	glLinkProgram(Handle);
	PrintGLError();
	int success;
	glGetProgramiv(Handle, GL_LINK_STATUS, &success);
	if(!success)
	{
		DebugLog("Shader linking failed:\n $", GetShaderProgramLog(Handle));
	}
	PrintGLError();
}

namespace
{
	const char* vertexShaderSource = 
	R"(
		#version 120
		
		attribute vec2 Position;
		attribute vec2 TextureCoordinate;
		attribute vec4 Color;
		
		varying vec2 texCoord;
		varying vec4 fragColor;

		void main()
		{
			texCoord = TextureCoordinate;
			gl_Position = vec4(Position, 0.0, 1.0);
			fragColor = Color;
		}
	)";

	const char* fragmentShaderSource =
	R"(
		#version 120
		
		varying vec2 texCoord;
		varying vec4 fragColor;
		uniform sampler2D TextureSampler;

		void main()
		{
			vec4 color = texture2D(TextureSampler, texCoord) * fragColor;
			gl_FragColor = color;
		}
	)";
}


ShaderProgram& ShaderProgram::GetDefaultShader()
{
	static ShaderProgram* retVal = nullptr;
	static Shader* fragment = nullptr;
	static Shader* vertex = nullptr;
	static PointerGuard<ShaderProgram> guard0(&retVal);
	static PointerGuard<Shader> guard1(&fragment);
	static PointerGuard<Shader> guard2(&vertex);
	
	if(!retVal)
	{
		retVal = new ShaderProgram;
		retVal->FragmentShader = fragment = new Shader(Shader::Fragment);
		retVal->VertexShader   = vertex   = new Shader(Shader::Vertex);
		retVal->FragmentShader->loadSourceFromBuffer(fragmentShaderSource);
		retVal->VertexShader  ->loadSourceFromBuffer(vertexShaderSource);
		retVal->FragmentShader->compile();
		retVal->VertexShader->compile();
		retVal->link();
		retVal->bindVertexAttribute(0, "Position");
		retVal->bindVertexAttribute(1, "TextureCoordinate");
		retVal->bindVertexAttribute(2, "Color");
	}
	
	return *retVal;
}

void ShaderProgram::bindVertexAttribute(int index, const char* attrib) const
{
	glBindAttribLocation(Handle, index, attrib);
	PrintGLError();
}

int ShaderProgram::getUniformIndex(const char* attrib) const
{
	return glGetUniformLocation(Handle, attrib);
}

void ShaderProgram::setUniform(int attrib, float val) const
{
	glUniform1f(attrib, val);
}

void ShaderProgram::setUniform(int attrib, Vec2F val) const
{
	glUniform2fv(attrib, 1, &(val[0]));
}

void ShaderProgram::setUniform(int attrib, Vec3F val) const
{
	glUniform3fv(attrib, 1, &(val[0]));
}

void ShaderProgram::setUniform(int attrib, Vec4F val) const
{
	glUniform4fv(attrib, 1, &(val[0]));
}

void ShaderProgram::setUniform(int attrib, int val) const
{
	glUniform1i(attrib, val);
}

void ShaderProgram::setUniform(int attrib, Vec2I val) const
{
	glUniform2iv(attrib, 1, &(val[0]));
}

void ShaderProgram::setUniform(int attrib, Vec3I val) const
{
	glUniform3iv(attrib, 1, &(val[0]));
}

void ShaderProgram::setUniform(int attrib, Vec4I val) const
{
	glUniform4iv(attrib, 1, &(val[0]));
}
