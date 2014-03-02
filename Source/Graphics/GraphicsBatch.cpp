#include "GraphicsBatch.h"
#include <GL/glew.h>
#include <Springbok/Graphics/Shader.h>
#include <Source/Utils/Debug.h>
#include <cstdlib>

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

	drawCommands.clear();
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

int FrameComparer (const void* p1, const void* p2)
{
	FrameData* data1 = (FrameData*)p1;
	FrameData* data2 = (FrameData*)p2;	

	if(data1->texture < data2->texture) return -1;
	if(data1->texture == data2->texture) return 0;
	if(data1->texture > data2->texture) return 1;

	return 0;
}

void GraphicsBatch::generateDrawCommands()
{
	DrawCommand current;
	current.texture = this->frameData[0].texture;
	current.count = 0;

	for(int i = 0; i < this->currentElement; i++)
	{
		if(current.texture != frameData[i].texture)
		{
			drawCommands.push_back(current);
			current = DrawCommand();
			current.texture = frameData[i].texture;
		}
		current.count++;	
	}
	drawCommands.push_back(current);
}

std::vector<unsigned short> GraphicsBatch::generateIndiciesList(int quadCount)
{
	std::vector<unsigned short> output;

	int index = 0;
	for(int i = 0; i < quadCount; i++)
	{
		output.push_back(index);
		index++;
		output.push_back(index);
		index++;
		output.push_back(index);
		index++;
		output.push_back(index);
		output.push_back(index);
		index++;	
		output.push_back(index);
	}	
	return output;
}

void GraphicsBatch::end()
{
	qsort(&frameData[0],this->currentElement,sizeof(FrameData),FrameComparer);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	for(int i = 0; i < this->currentElement; i++)
	{
		VertexArray<4>& vertices = frameData[i].vertices; 
		glBufferSubData(GL_ARRAY_BUFFER,this->vertexBufferOffset,4*2*sizeof(float),vertices.data());	
		this->vertexBufferOffset += 4*2*sizeof(float); 
	}

	glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
	for(int i = 0; i < this->currentElement; i++)
	{
		RectF& texCoords = frameData[i].textureCoordinates; 
		glBufferSubData(GL_ARRAY_BUFFER,this->textureBufferOffset,4*2*sizeof(float),texCoords.Points);	
		this->textureBufferOffset += 4*2*sizeof(float); 
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	std::vector<unsigned short> indices = this->generateIndiciesList(this->currentElement);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short),&indices[0], GL_DYNAMIC_DRAW);

	this->generateDrawCommands();

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

	int drawOffset = 0;

	for(unsigned int i = 0; i < this->drawCommands.size(); i++)
	{
		glBindTexture(GL_TEXTURE_2D,this->drawCommands[i].texture);
		glDrawElements(GL_TRIANGLE_STRIP, this->drawCommands[i].count * 6, GL_UNSIGNED_SHORT, (void*)(drawOffset * sizeof(unsigned short)));
		drawOffset += 6* this->drawCommands[i].count;
	}

	glDisableVertexAttribArray(vertexAttributeLocation);
}

void GraphicsBatch::lazyInit()
{
	if(this->isInit)
		return;
	
	this->isInit = true;
	glGenBuffers(1,&this->vertexBuffer);	
	glGenBuffers(1,&this->textureBuffer);
	glGenBuffers(1,&this->elementBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, (4*2*sizeof(float))*this->size, NULL, GL_DYNAMIC_DRAW);   

	glBindBuffer(GL_ARRAY_BUFFER, this->textureBuffer);
	glBufferData(GL_ARRAY_BUFFER, (4*2*sizeof(float))*this->size, NULL, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->elementBuffer);

	shader = new Shader(vertexShader,fragmentShader);
}

