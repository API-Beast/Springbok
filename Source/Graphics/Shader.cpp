#include "Shader.h"
#include "GL/glew.h"
#include <Springbok/Utils/Debug.h>

Shader::Shader(std::string vertexShader, std::string fragmentShader)
{
	glHandle vertex = this->compileVertexShader(vertexShader.c_str());
	glHandle fragment = this->compileFragmentShader(fragmentShader.c_str());

	this->handle = this->link(vertex,fragment);
}

glHandle Shader::compileVertexShader(const char* vertexShader)
{
	Debug::Write("Compile vertex shader...");
	glHandle vertexHandle = glCreateShader(GL_VERTEX_SHADER);
	int result = 0;

	glShaderSource(vertexHandle, 1, &vertexShader, NULL);	
	glCompileShader(vertexHandle);
	glGetShaderiv(vertexHandle, GL_COMPILE_STATUS, &result);
	Debug::Write(getShaderLog(vertexHandle).c_str());

	if(!result)
		Debug::Write("Compile failed!");

	return vertexHandle;
}

glHandle Shader::compileFragmentShader(const char* fragmentShader)
{
	Debug::Write("Compile fragment shader...");
	glHandle fragmentHandle = glCreateShader(GL_FRAGMENT_SHADER);	
	int result = 0;

	glShaderSource(fragmentHandle, 1, &fragmentShader, NULL);	
	glCompileShader(fragmentHandle);
	glGetShaderiv(fragmentHandle, GL_COMPILE_STATUS, &result);
	Debug::Write(getShaderLog(fragmentHandle).c_str());

	if(!result)
		Debug::Write("Compile failed!");

	return fragmentHandle;
}

glHandle Shader::link(glHandle vertexShader, glHandle fragmentShader)
{
	Debug::Write("Linking shader...");	
	int result = 0;
	glHandle programHandle = glCreateProgram();

	glAttachShader(programHandle, vertexShader);	
	glAttachShader(programHandle, fragmentShader);
	glLinkProgram(programHandle);

	glGetProgramiv(programHandle, GL_LINK_STATUS, &result);
	Debug::Write(getProgramLog(programHandle).c_str());
	
	if(!result)
		Debug::Write("Linking failed!");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	valid = result == 1;

	//attributeLocation["VertexPosition"] = glGetAttribLocation(handle, "VertexPosition");

	return programHandle;
}

std::string Shader::getShaderLog(glHandle id)
{
	int infoLogLength;
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
	std::string output(infoLogLength, ' ');
	glGetShaderInfoLog(id, infoLogLength, NULL, &output[0]);
	if (!output.empty()) {
		if (output.back() == '\n') // Brrr I hate that last new line
			output.substr(0, output.size() - 1);
	}
	return output;
}

std::string Shader::getProgramLog(glHandle id)
{
	int infoLogLength;
	glGetProgramiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
	std::string output(infoLogLength, ' ');
	glGetProgramInfoLog(id, infoLogLength, NULL, &output[0]);
	if (!output.empty()) {
		if (output.back() == '\n') // Brrr I hate that last new line
			output.substr(0, output.size() - 1);
	}
	return output;
}

void Shader::bind()
{
	if(!valid) {
		Debug::Write("Tried to use invalid shader $!",handle);
		return;
	}

	glUseProgram(handle);
}

int Shader::getUniformLocation(std::string name)
{
	if(!uniformLocation.count(name))
		uniformLocation[name] = glGetUniformLocation(handle,name.c_str());
	return uniformLocation[name]; 
}

int Shader::getAttributeLocation(std::string name)
{
	if (!attributeLocation.count(name))
		attributeLocation[name] = glGetAttribLocation(handle, name.c_str());
	if (attributeLocation[name] == -1) {
		attributeLocation[name] = glGetAttribLocation(handle, name.c_str());
		Debug::Write("WARNING: Invalid location for $!",name);
	}

	return attributeLocation[name];
}

void Shader::buildUniformList()
{

}

void Shader::buildAttributeList()
{

}

void Shader::setUniform(std::string name, int value)
{
	int location = this->getUniformLocation(name);
	glUniform1i(location, value);
}
