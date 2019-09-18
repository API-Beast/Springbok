//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "GLES2.h"
#include <Springbok/Platform/GameSurface.h>
#include <Springbok/Utils/Functions.h>

namespace FunctionPointers
{
	void (*glActiveTexture)(GLenum texture) = nullptr;
	void (*glAttachShader)(GLuint program, GLuint shader) = nullptr;
	void (*glBindAttribLocation)(GLuint program, GLuint index, const GLchar *name) = nullptr;
	void (*glBindBuffer)(GLenum target, GLuint buffer) = nullptr;
	void (*glBindFramebuffer)(GLenum target, GLuint framebuffer) = nullptr;
	void (*glBindRenderbuffer)(GLenum target, GLuint renderbuffer) = nullptr;
	void (*glBindTexture)(GLenum target, GLuint texture) = nullptr;
	void (*glBlendColor)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) = nullptr;
	void (*glBlendEquation)(GLenum mode) = nullptr;
	void (*glBlendEquationSeparate)(GLenum modeRGB, GLenum modeAlpha) = nullptr;
	void (*glBlendFunc)(GLenum sfactor, GLenum dfactor) = nullptr;
	void (*glBlendFuncSeparate)(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha) = nullptr;
	void (*glBufferData)(GLenum target, GLsizeiptr size, const void *data, GLenum usage) = nullptr;
	void (*glBufferSubData)(GLenum target, GLintptr offset, GLsizeiptr size, const void *data) = nullptr;
	GLenum (*glCheckFramebufferStatus)(GLenum target) = nullptr;
	void (*glClearDepthf)(GLfloat d) = nullptr;
	void (*glClearStencil)(GLint s) = nullptr;
	void (*glColorMask)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) = nullptr;
	void (*glCompileShader)(GLuint shader) = nullptr;
	void (*glCompressedTexImage2D)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void *data) = nullptr;
	void (*glCompressedTexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data) = nullptr;
	void (*glCopyTexImage2D)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border) = nullptr;
	void (*glCopyTexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) = nullptr;
	GLuint (*glCreateProgram)(void) = nullptr;
	GLuint (*glCreateShader)(GLenum type) = nullptr;
	void (*glCullFace)(GLenum mode) = nullptr;
	void (*glDeleteBuffers)(GLsizei n, const GLuint *buffers) = nullptr;
	void (*glDeleteFramebuffers)(GLsizei n, const GLuint *framebuffers) = nullptr;
	void (*glDeleteProgram)(GLuint program) = nullptr;
	void (*glDeleteRenderbuffers)(GLsizei n, const GLuint *renderbuffers) = nullptr;
	void (*glDeleteShader)(GLuint shader) = nullptr;
	void (*glDeleteTextures)(GLsizei n, const GLuint *textures) = nullptr;
	void (*glDepthFunc)(GLenum func) = nullptr;
	void (*glDepthMask)(GLboolean flag) = nullptr;
	void (*glDepthRangef)(GLfloat n, GLfloat f) = nullptr;
	void (*glDetachShader)(GLuint program, GLuint shader) = nullptr;
	void (*glDisable)(GLenum cap) = nullptr;
	void (*glDisableVertexAttribArray)(GLuint index) = nullptr;
	void (*glDrawArrays)(GLenum mode, GLint first, GLsizei count) = nullptr;
	void (*glDrawElements)(GLenum mode, GLsizei count, GLenum type, const void *indices) = nullptr;
	void (*glEnable)(GLenum cap) = nullptr;
	void (*glEnableVertexAttribArray)(GLuint index) = nullptr;
	void (*glFinish)(void) = nullptr;
	void (*glFlush)(void) = nullptr;
	void (*glFramebufferRenderbuffer)(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) = nullptr;
	void (*glFramebufferTexture2D)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) = nullptr;
	void (*glFrontFace)(GLenum mode) = nullptr;
	void (*glGenBuffers)(GLsizei n, GLuint *buffers) = nullptr;
	void (*glGenerateMipmap)(GLenum target) = nullptr;
	void (*glGenFramebuffers)(GLsizei n, GLuint *framebuffers) = nullptr;
	void (*glGenRenderbuffers)(GLsizei n, GLuint *renderbuffers) = nullptr;
	void (*glGenTextures)(GLsizei n, GLuint *textures) = nullptr;
	void (*glGetActiveAttrib)(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name) = nullptr;
	void (*glGetActiveUniform)(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name) = nullptr;
	void (*glGetAttachedShaders)(GLuint program, GLsizei maxCount, GLsizei *count, GLuint *shaders) = nullptr;
	GLint (*glGetAttribLocation)(GLuint program, const GLchar *name) = nullptr;
	void (*glGetBooleanv)(GLenum pname, GLboolean *data) = nullptr;
	void (*glGetBufferParameteriv)(GLenum target, GLenum pname, GLint *params) = nullptr;
	void (*glGetFloatv)(GLenum pname, GLfloat *data) = nullptr;
	void (*glGetFramebufferAttachmentParameteriv)(GLenum target, GLenum attachment, GLenum pname, GLint *params) = nullptr;
	void (*glGetProgramiv)(GLuint program, GLenum pname, GLint *params) = nullptr;
	void (*glGetProgramInfoLog)(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog) = nullptr;
	void (*glGetRenderbufferParameteriv)(GLenum target, GLenum pname, GLint *params) = nullptr;
	void (*glGetShaderiv)(GLuint shader, GLenum pname, GLint *params) = nullptr;
	void (*glGetShaderInfoLog)(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog) = nullptr;
	void (*glGetShaderPrecisionFormat)(GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision) = nullptr;
	void (*glGetShaderSource)(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source) = nullptr;
	void (*glGetTexParameterfv)(GLenum target, GLenum pname, GLfloat *params) = nullptr;
	void (*glGetTexParameteriv)(GLenum target, GLenum pname, GLint *params) = nullptr;
	void (*glGetUniformfv)(GLuint program, GLint location, GLfloat *params) = nullptr;
	void (*glGetUniformiv)(GLuint program, GLint location, GLint *params) = nullptr;
	GLint (*glGetUniformLocation)(GLuint program, const GLchar *name) = nullptr;
	void (*glGetVertexAttribfv)(GLuint index, GLenum pname, GLfloat *params) = nullptr;
	void (*glGetVertexAttribiv)(GLuint index, GLenum pname, GLint *params) = nullptr;
	void (*glGetVertexAttribPointerv)(GLuint index, GLenum pname, void **pointer) = nullptr;
	void (*glHint)(GLenum target, GLenum mode) = nullptr;
	GLboolean (*glIsBuffer)(GLuint buffer) = nullptr;
	GLboolean (*glIsEnabled)(GLenum cap) = nullptr;
	GLboolean (*glIsFramebuffer)(GLuint framebuffer) = nullptr;
	GLboolean (*glIsProgram)(GLuint program) = nullptr;
	GLboolean (*glIsRenderbuffer)(GLuint renderbuffer) = nullptr;
	GLboolean (*glIsShader)(GLuint shader) = nullptr;
	GLboolean (*glIsTexture)(GLuint texture) = nullptr;
	void (*glLineWidth)(GLfloat width) = nullptr;
	void (*glLinkProgram)(GLuint program) = nullptr;
	void (*glPixelStorei)(GLenum pname, GLint param) = nullptr;
	void (*glPolygonOffset)(GLfloat factor, GLfloat units) = nullptr;
	void (*glReadPixels)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void *pixels) = nullptr;
	void (*glReleaseShaderCompiler)(void) = nullptr;
	void (*glRenderbufferStorage)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height) = nullptr;
	void (*glSampleCoverage)(GLfloat value, GLboolean invert) = nullptr;
	void (*glScissor)(GLint x, GLint y, GLsizei width, GLsizei height) = nullptr;
	void (*glShaderBinary)(GLsizei count, const GLuint *shaders, GLenum binaryformat, const void *binary, GLsizei length) = nullptr;
	void (*glShaderSource)(GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length) = nullptr;
	void (*glStencilFunc)(GLenum func, GLint ref, GLuint mask) = nullptr;
	void (*glStencilFuncSeparate)(GLenum face, GLenum func, GLint ref, GLuint mask) = nullptr;
	void (*glStencilMask)(GLuint mask) = nullptr;
	void (*glStencilMaskSeparate)(GLenum face, GLuint mask) = nullptr;
	void (*glStencilOp)(GLenum fail, GLenum zfail, GLenum zpass) = nullptr;
	void (*glStencilOpSeparate)(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass) = nullptr;
	void (*glTexImage2D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels) = nullptr;
	void (*glTexParameterf)(GLenum target, GLenum pname, GLfloat param) = nullptr;
	void (*glTexParameterfv)(GLenum target, GLenum pname, const GLfloat *params) = nullptr;
	void (*glTexParameteri)(GLenum target, GLenum pname, GLint param) = nullptr;
	void (*glTexParameteriv)(GLenum target, GLenum pname, const GLint *params) = nullptr;
	void (*glTexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels) = nullptr;
	void (*glUniform1f)(GLint location, GLfloat v0) = nullptr;
	void (*glUniform1fv)(GLint location, GLsizei count, const GLfloat *value) = nullptr;
	void (*glUniform1i)(GLint location, GLint v0) = nullptr;
	void (*glUniform1iv)(GLint location, GLsizei count, const GLint *value) = nullptr;
	void (*glUniform2f)(GLint location, GLfloat v0, GLfloat v1) = nullptr;
	void (*glUniform2fv)(GLint location, GLsizei count, const GLfloat *value) = nullptr;
	void (*glUniform2i)(GLint location, GLint v0, GLint v1) = nullptr;
	void (*glUniform2iv)(GLint location, GLsizei count, const GLint *value) = nullptr;
	void (*glUniform3f)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2) = nullptr;
	void (*glUniform3fv)(GLint location, GLsizei count, const GLfloat *value) = nullptr;
	void (*glUniform3i)(GLint location, GLint v0, GLint v1, GLint v2) = nullptr;
	void (*glUniform3iv)(GLint location, GLsizei count, const GLint *value) = nullptr;
	void (*glUniform4f)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) = nullptr;
	void (*glUniform4fv)(GLint location, GLsizei count, const GLfloat *value) = nullptr;
	void (*glUniform4i)(GLint location, GLint v0, GLint v1, GLint v2, GLint v3) = nullptr;
	void (*glUniform4iv)(GLint location, GLsizei count, const GLint *value) = nullptr;
	void (*glUniformMatrix2fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) = nullptr;
	void (*glUniformMatrix3fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) = nullptr;
	void (*glUniformMatrix4fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) = nullptr;
	void (*glUseProgram)(GLuint program) = nullptr;
	void (*glValidateProgram)(GLuint program) = nullptr;
	void (*glVertexAttrib1f)(GLuint index, GLfloat x) = nullptr;
	void (*glVertexAttrib1fv)(GLuint index, const GLfloat *v) = nullptr;
	void (*glVertexAttrib2f)(GLuint index, GLfloat x, GLfloat y) = nullptr;
	void (*glVertexAttrib2fv)(GLuint index, const GLfloat *v) = nullptr;
	void (*glVertexAttrib3f)(GLuint index, GLfloat x, GLfloat y, GLfloat z) = nullptr;
	void (*glVertexAttrib3fv)(GLuint index, const GLfloat *v) = nullptr;
	void (*glVertexAttrib4f)(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) = nullptr;
	void (*glVertexAttrib4fv)(GLuint index, const GLfloat *v) = nullptr;
	void (*glVertexAttribPointer)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer) = nullptr;

	GLuint (*glGetDebugMessageLog)(GLuint count, GLsizei bufSize, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog) = nullptr;
	void (*glGenVertexArrays)(GLsizei n, GLuint *arrays) = nullptr;
	void (*glBindVertexArray)(GLuint array) = nullptr;
};

bool LoadOpenGLFunctions(GameSurface* surface)
{
	bool failure = false;
#define oglLoadFunc(A) FunctionPointers::A = surface->getGLFunction<decltype(FunctionPointers::A)>(#A); if(FunctionPointers::A == nullptr){ DebugLog("Couldn't load OpenGL function $", #A); failure = true; }
	oglLoadFunc(glActiveTexture);
	oglLoadFunc(glAttachShader);
	oglLoadFunc(glBindAttribLocation);
	oglLoadFunc(glBindBuffer);
	oglLoadFunc(glBindFramebuffer);
	oglLoadFunc(glBindRenderbuffer);
	oglLoadFunc(glBindTexture);
	oglLoadFunc(glBlendColor);
	oglLoadFunc(glBlendEquation);
	oglLoadFunc(glBlendEquationSeparate);
	oglLoadFunc(glBlendFunc);
	oglLoadFunc(glBlendFuncSeparate);
	oglLoadFunc(glBufferData);
	oglLoadFunc(glBufferSubData);
	oglLoadFunc(glCheckFramebufferStatus);
	oglLoadFunc(glClearDepthf);
	oglLoadFunc(glClearStencil);
	oglLoadFunc(glColorMask);
	oglLoadFunc(glCompileShader);
	oglLoadFunc(glCompressedTexImage2D);
	oglLoadFunc(glCompressedTexSubImage2D);
	oglLoadFunc(glCopyTexImage2D);
	oglLoadFunc(glCopyTexSubImage2D);
	oglLoadFunc(glCreateProgram);
	oglLoadFunc(glCreateShader);
	oglLoadFunc(glCullFace);
	oglLoadFunc(glDeleteBuffers);
	oglLoadFunc(glDeleteFramebuffers);
	oglLoadFunc(glDeleteProgram);
	oglLoadFunc(glDeleteRenderbuffers);
	oglLoadFunc(glDeleteShader);
	oglLoadFunc(glDeleteTextures);
	oglLoadFunc(glDepthFunc);
	oglLoadFunc(glDepthMask);
	oglLoadFunc(glDepthRangef);
	oglLoadFunc(glDetachShader);
	oglLoadFunc(glDisable);
	oglLoadFunc(glDisableVertexAttribArray);
	oglLoadFunc(glDrawArrays);
	oglLoadFunc(glDrawElements);
	oglLoadFunc(glEnable);
	oglLoadFunc(glEnableVertexAttribArray);
	oglLoadFunc(glFinish);
	oglLoadFunc(glFlush);
	oglLoadFunc(glFramebufferRenderbuffer);
	oglLoadFunc(glFramebufferTexture2D);
	oglLoadFunc(glFrontFace);
	oglLoadFunc(glGenBuffers);
	oglLoadFunc(glGenerateMipmap);
	oglLoadFunc(glGenFramebuffers);
	oglLoadFunc(glGenRenderbuffers);
	oglLoadFunc(glGenTextures);
	oglLoadFunc(glGetActiveAttrib);
	oglLoadFunc(glGetActiveUniform);
	oglLoadFunc(glGetAttachedShaders);
	oglLoadFunc(glGetAttribLocation);
	oglLoadFunc(glGetBooleanv);
	oglLoadFunc(glGetBufferParameteriv);
	oglLoadFunc(glGetFloatv);
	oglLoadFunc(glGetFramebufferAttachmentParameteriv);
	oglLoadFunc(glGetProgramiv);
	oglLoadFunc(glGetProgramInfoLog);
	oglLoadFunc(glGetRenderbufferParameteriv);
	oglLoadFunc(glGetShaderiv);
	oglLoadFunc(glGetShaderInfoLog);
	oglLoadFunc(glGetShaderPrecisionFormat);
	oglLoadFunc(glGetShaderSource);
	oglLoadFunc(glGetTexParameterfv);
	oglLoadFunc(glGetTexParameteriv);
	oglLoadFunc(glGetUniformfv);
	oglLoadFunc(glGetUniformiv);
	oglLoadFunc(glGetUniformLocation);
	oglLoadFunc(glGetVertexAttribfv);
	oglLoadFunc(glGetVertexAttribiv);
	oglLoadFunc(glGetVertexAttribPointerv);
	oglLoadFunc(glHint);
	oglLoadFunc(glIsBuffer);
	oglLoadFunc(glIsEnabled);
	oglLoadFunc(glIsFramebuffer);
	oglLoadFunc(glIsProgram);
	oglLoadFunc(glIsRenderbuffer);
	oglLoadFunc(glIsShader);
	oglLoadFunc(glIsTexture);
	oglLoadFunc(glLineWidth);
	oglLoadFunc(glLinkProgram);
	oglLoadFunc(glPixelStorei);
	oglLoadFunc(glPolygonOffset);
	oglLoadFunc(glReadPixels);
	oglLoadFunc(glReleaseShaderCompiler);
	oglLoadFunc(glRenderbufferStorage);
	oglLoadFunc(glSampleCoverage);
	oglLoadFunc(glScissor);
	oglLoadFunc(glShaderBinary);
	oglLoadFunc(glShaderSource);
	oglLoadFunc(glStencilFunc);
	oglLoadFunc(glStencilFuncSeparate);
	oglLoadFunc(glStencilMask);
	oglLoadFunc(glStencilMaskSeparate);
	oglLoadFunc(glStencilOp);
	oglLoadFunc(glStencilOpSeparate);
	oglLoadFunc(glTexImage2D);
	oglLoadFunc(glTexParameterf);
	oglLoadFunc(glTexParameterfv);
	oglLoadFunc(glTexParameteri);
	oglLoadFunc(glTexParameteriv);
	oglLoadFunc(glTexSubImage2D);
	oglLoadFunc(glUniform1f);
	oglLoadFunc(glUniform1fv);
	oglLoadFunc(glUniform1i);
	oglLoadFunc(glUniform1iv);
	oglLoadFunc(glUniform2f);
	oglLoadFunc(glUniform2fv);
	oglLoadFunc(glUniform2i);
	oglLoadFunc(glUniform2iv);
	oglLoadFunc(glUniform3f);
	oglLoadFunc(glUniform3fv);
	oglLoadFunc(glUniform3i);
	oglLoadFunc(glUniform3iv);
	oglLoadFunc(glUniform4f);
	oglLoadFunc(glUniform4fv);
	oglLoadFunc(glUniform4i);
	oglLoadFunc(glUniform4iv);
	oglLoadFunc(glUniformMatrix2fv);
	oglLoadFunc(glUniformMatrix3fv);
	oglLoadFunc(glUniformMatrix4fv);
	oglLoadFunc(glUseProgram);
	oglLoadFunc(glValidateProgram);
	oglLoadFunc(glVertexAttrib1f);
	oglLoadFunc(glVertexAttrib1fv);
	oglLoadFunc(glVertexAttrib2f);
	oglLoadFunc(glVertexAttrib2fv);
	oglLoadFunc(glVertexAttrib3f);
	oglLoadFunc(glVertexAttrib3fv);
	oglLoadFunc(glVertexAttrib4f);
	oglLoadFunc(glVertexAttrib4fv);
	oglLoadFunc(glVertexAttribPointer);
	// Additional functions
	oglLoadFunc(glGetDebugMessageLog);
	oglLoadFunc(glGenVertexArrays);
	oglLoadFunc(glBindVertexArray);
#undef oglLoadFunc
	return !failure;
};

bool _PrintGLError(const char* file, int line)
{
	while(true)
	{
		GLchar bfr[512];
		GLenum source[5];
		GLenum type[5];
		GLuint id[5];
		GLenum severity[5];
		GLsizei length[5];
		auto msgs = glGetDebugMessageLog(1, 512, source, type, id, severity, length, bfr);
		if(msgs)
		{
			bfr[512*5-1] = '\0';
			DebugLog("$ at line $\n$", file, line, bfr);
		}
		else
			break;
	}
	
	/*GLenum error = glGetError();
	if(error != GL_NO_ERROR)
	{
		std::string errorStr = "???";
	
		switch(error)
		{
						case GL_INVALID_OPERATION:      				errorStr="INVALID_OPERATION";      break;
						case GL_INVALID_ENUM:           				errorStr="INVALID_ENUM";           break;
						case GL_INVALID_VALUE:          				errorStr="INVALID_VALUE";          break;
						case GL_OUT_OF_MEMORY:          				errorStr="OUT_OF_MEMORY";          break;
						case GL_INVALID_FRAMEBUFFER_OPERATION:  errorStr="INVALID_FRAMEBUFFER_OPERATION";  break;
		}
		DebugLog("$ at line $\n OpenGL Error: $ -> $", file, line, error, errorStr);
		return true;
	}*/
	return false;
};