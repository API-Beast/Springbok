#include "GraphicsBatch.h"
#include <GL/glew.h>
#include <Springbok/Graphics/Shader.h>
#include <Source/Utils/Debug.h>

const char* vertexShader = 
"attribute vec2 VertexPosition;"
""
"void main() {"
"gl_Position.xyz = vec3(VertexPosition.x,VertexPosition.y,0);"
"gl_Position.w = 1.0;"
"}";

const char* fragmentShader =
"void main(){"
"gl_FragColor = vec4(1,0,0,1);" 
"}";

GraphicsBatch::GraphicsBatch(int size)
{
	this->frameData.reserve(size);
	this->size = size;
}

void GraphicsBatch::Start()
{
	this->lazyInit();
	bufferOffset = 0;
	currentElement = 0;
}

void GraphicsBatch::Draw(VertexArray<4> data)
{
	if(currentElement >= this->size) {
		Debug::Write("WARNING: Draw command discarded because your batch is too small! You wanted to draw more than $ images in one batch!",this->size);
		return;
	}
	frameData[currentElement] = data;
	currentElement++;
}

void GraphicsBatch::End()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	for(int i = 0; i < this->size; i++)
	{
		VertexArray<4>& vertices = frameData[i]; 
		glBufferSubData(GL_ARRAY_BUFFER,this->bufferOffset,4*2*sizeof(float),vertices.data());	
		this->bufferOffset += 4*2*sizeof(float); 
	}

	shader->bind();

	int vertexAttributeLocation = shader->getAttributeLocation("VertexPosition");

	glEnableVertexAttribArray(vertexAttributeLocation);
	glVertexAttribPointer(vertexAttributeLocation, 2, GL_FLOAT, false, 0, 0);

	static const GLubyte indices[4] = {0, 1, 2, 3};
	glDrawArrays(GL_QUADS, 0, 4*(this->bufferOffset / (4*2*sizeof(float))));

	glDisableVertexAttribArray(vertexAttributeLocation);
}

void GraphicsBatch::lazyInit()
{
	if(this->isInit)
		return;
	
	this->isInit = true;
	glGenBuffers(1,&this->vertexBuffer);	
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, (4*2*sizeof(float))*this->size, NULL, GL_DYNAMIC_DRAW);   
	shader = new Shader(vertexShader,fragmentShader);
}

