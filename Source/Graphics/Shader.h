#pragma once

#include <string>
#include <map>
#include "GLTypes.h"

class Shader
{
public:
	Shader(std::string vertexShader, std::string fragmentShader);
	void bind();
public:
	bool isValid() const { return valid; }
	glHandle getHandle() const { return handle; }
	int getUniformLocation(std::string name);
	int getAttributeLocation(std::string name);
public:
	void setUniform(std::string name, int value);
	//void SetUniform(std::string name, glm::mat4 value);
private:
	glHandle compileVertexShader(const char* vertexShader);
	glHandle compileFragmentShader(const char* fragmentShader);
	glHandle link(glHandle vertexShader, glHandle fragmentShader);
	std::string getShaderLog(glHandle id);
	std::string getProgramLog(glHandle id);
	void buildUniformList();
	void buildAttributeList();
private:
	glHandle handle;
	std::map<std::string, int> uniformLocation;
	std::map<std::string, int> attributeLocation;
	bool valid = false;
};
