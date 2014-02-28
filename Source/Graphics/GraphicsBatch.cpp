#include "GraphicsBatch.h"
#include <GL/glew.h>
#include <Springbok/Graphics/Shader.h>

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


GraphicsBatch::GraphicsBatch()
{

}

void GraphicsBatch::Start()
{
	this->lazyInit();
	bufferOffset = 0;
}

void GraphicsBatch::Draw(VertexArray<4> data)
{
	frameData.push(data);
}

void GraphicsBatch::End()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	while(frameData.size() > 0)
	{
		VertexArray<4>& vertices = frameData.top();
		glBufferSubData(GL_ARRAY_BUFFER,this->bufferOffset,4*2*sizeof(float),vertices.data());	
		this->bufferOffset += 4*2*sizeof(float); 
		frameData.pop();
	}

	shader->bind();

	int vertexAttributeLocation = shader->getAttributeLocation("VertexPosition");

	glEnableVertexAttribArray(vertexAttributeLocation);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
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
	glBufferData(GL_ARRAY_BUFFER, (4*2*sizeof(float))*3, NULL, GL_DYNAMIC_DRAW);   
	shader = new Shader(vertexShader,fragmentShader);
}

