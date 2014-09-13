//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "Shader.h"
#include <Springbok/Foundation/ObjectPointer.h>
#include <Springbok/Foundation/Vec4.h>

struct ShaderProgram
{
	ObjectPointer<Shader> VertexShader;
	ObjectPointer<Shader> FragmentShader;
	GLuint Handle = 0;
	
	ShaderProgram() = default;
	ShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	ShaderProgram(const std::string& fragmentShaderPath);
	
	void loadVertexShader(const std::string& path);
	void loadFragmentShader(const std::string& path);
	
	void bindVertexAttribute(int index, const char* attrib) const;
	int getUniformIndex(const char* attrib) const;
	
	void setUniform(int attrib, float val) const;
	void setUniform(int attrib, Vec2F val) const;
	void setUniform(int attrib, Vec3F val) const;
	void setUniform(int attrib, Vec4F val) const;
	
	void setUniform(int attrib, int val)   const;
	void setUniform(int attrib, Vec2I val) const;
	void setUniform(int attrib, Vec3I val) const;
	void setUniform(int attrib, Vec4I val) const;
	
	template<typename T>
	void setUniform(const char* attrib, T val) const{ return setUniform(getUniformIndex(attrib), val); };
	
	void deleteShader();
	bool link();
	
	static ShaderProgram& GetDefaultShader();
};