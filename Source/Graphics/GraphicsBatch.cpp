#include "GraphicsBatch.h"
#include <GL/glew.h>
#include <Springbok/Graphics/Shader.h>
#include <Source/Utils/Debug.h>

const char* vertexShader = 
"attribute vec2 VertexPosition;"
"attribute vec2 TextureCoordinate;"
"varying vec2 texCoord;"
""
"void main() {"
"texCoord = TextureCoordinate;"
"gl_Position.xyz = vec3(VertexPosition.x,VertexPosition.y,0);"
"gl_Position.w = 1.0;"
"}";

const char* fragmentShader =
"precision mediump float;"
"varying vec2 texCoord;"
"uniform sampler2D TextureSampler;"
""
"void main(){"
"gl_FragColor = texture2D(TextureSampler, vec2(texCoord.s, texCoord.t));" 
"}";

/*
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
*/
GraphicsBatch::GraphicsBatch(int size)
{
	this->frameData.reserve(size);
	this->size = size;
}

void GraphicsBatch::start()
{
	this->lazyInit();
	vertexBufferOffset = 0;
	textureBufferOffset = 0;
	currentElement = 0;
}

void GraphicsBatch::draw(ObjectPointer<Texture> texture, VertexArray<4> data)
{
	if(currentElement >= this->size) {
		Debug::Write("WARNING: Draw command discarded because your batch is too small! You wanted to draw more than $ images in one batch!",this->size);
		return;
	}
	frameData[currentElement] = FrameData(data,texture->TextureCoordinates,texture->Index);
	currentElement++;
}

void GraphicsBatch::end()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	for(int i = 0; i < this->size; i++)
	{
		VertexArray<4>& vertices = frameData[i].vertices; 
		glBufferSubData(GL_ARRAY_BUFFER,this->vertexBufferOffset,4*2*sizeof(float),vertices.data());	
		this->vertexBufferOffset += 4*2*sizeof(float); 
	}

	glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
	for(int i = 0; i < this->size; i++)
	{
		RectF& texCoords = frameData[i].textureCoordinates; 
		glBufferSubData(GL_ARRAY_BUFFER,this->textureBufferOffset,4*2*sizeof(float),texCoords.Points);	
		this->textureBufferOffset += 4*2*sizeof(float); 
	}

	glBindTexture(GL_TEXTURE_2D, frameData[0].texture);
	shader->bind();
	shader->setUniform("TextureSampler",0);

	int vertexAttributeLocation = shader->getAttributeLocation("VertexPosition");
	int textureAttributeLocation = shader->getAttributeLocation("TextureCoordinate");

	glEnableVertexAttribArray(vertexAttributeLocation);
	glEnableVertexAttribArray(textureAttributeLocation);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(vertexAttributeLocation, 2, GL_FLOAT, false, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
	glVertexAttribPointer(textureAttributeLocation, 2, GL_FLOAT, false, 0, 0);

	static const GLubyte indices[4] = {0, 1, 2, 3};
	glDrawArrays(GL_QUADS, 0, 4*(this->vertexBufferOffset / (4*2*sizeof(float))));

	glDisableVertexAttribArray(vertexAttributeLocation);
}

void GraphicsBatch::lazyInit()
{
	if(this->isInit)
		return;
	
	this->isInit = true;
	glGenBuffers(1,&this->vertexBuffer);	
	glGenBuffers(1,&this->textureBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, (4*2*sizeof(float))*this->size, NULL, GL_DYNAMIC_DRAW);   

	glBindBuffer(GL_ARRAY_BUFFER, this->textureBuffer);
	glBufferData(GL_ARRAY_BUFFER, (4*2*sizeof(float))*this->size, NULL, GL_DYNAMIC_DRAW);

	shader = new Shader(vertexShader,fragmentShader);
}

