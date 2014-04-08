//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "Framebuffer.h"
#include "Core/GLES2.h"
#include <Springbok/Utils/Debug.h>

Framebuffer::Framebuffer(int width, int height, int precision)
{
	glGenFramebuffers(1, &Index);
	if(PrintGLError() || !Index)
	{
		Valid = false;
		Index = 0;
		return ;
	}
	ColorAttachment = new Texture(width, height, precision);
	ColorAttachment->disableFiltering();
	unsigned int previousFramebuffer;
	int temp;
	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &temp);
	previousFramebuffer = temp;
	glBindFramebuffer(GL_FRAMEBUFFER, Index);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ColorAttachment->Index, 0);
	PrintGLError();
	
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if(status != GL_FRAMEBUFFER_COMPLETE)
	{
		std::string errorStr = "???";
		switch(status)
		{
						case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:         errorStr="INCOMPLETE_ATTACHMENT"; break;
						case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS: 				 errorStr="INCOMPLETE_DIMENSIONS"; break;
						case GL_FRAMEBUFFER_UNSUPPORTED:           				 errorStr="UNSUPPORTED";           break;
						case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT: errorStr="INCOMPLETE_MISSING_ATTACHMENT"; break;
		}
		Debug::Write("Framebuffer($, $)\n OpenGL Framebuffer Incomplete: $ -> $", width, height, status, errorStr);
		ColorAttachment.destroy();
		glDeleteFramebuffers(1, &Index);
		return;
	}
	
	glBindFramebuffer(GL_FRAMEBUFFER, previousFramebuffer);
	Valid = true;
}

Framebuffer::~Framebuffer()
{
	if(Valid)
	{
		ColorAttachment.destroy();
		glDeleteFramebuffers(1, &Index);
	}
}

void Framebuffer::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, Index);
}

Vec2F Framebuffer::size() const
{
	return ColorAttachment->ImageSize;
}