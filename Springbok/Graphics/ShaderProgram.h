//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "Shader.h"
#include <Springbok/Generic/ObjectPointer.h>

struct ShaderProgram
{
	ObjectPointer<Shader> VertexShader;
	ObjectPointer<Shader> FragmentShader;
	GLuint Handle = 0;
	
	ShaderProgram() = default;
	ShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	
	void bindVertexAttribute(int index, const char* attrib);
	void deleteShader();
	bool link();
	
	static ShaderProgram& GetDefaultShader();
};