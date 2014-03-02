#pragma once

#include <Springbok/Containers/VertexArray.h>
#include <Springbok/Generic/ObjectPointer.h>
#include "GLTypes.h"
#include "Texture.h"
#include <vector>
#include <map>

class Shader;

struct FrameData
{
	FrameData(VertexArray<4> vertices, RectF textureCoordinates, glHandle texture)
	{
		this->vertices = vertices;
	 	this->textureCoordinates = textureCoordinates;
		this->texture = texture;
	}

	VertexArray<4> vertices;
	RectF textureCoordinates;

	glHandle texture;
};

struct DrawCommand
{
	glHandle texture;
	int count;
};

class GraphicsBatch
{
public:
	GraphicsBatch(int size = 256);
public:
	void start();
	void draw(ObjectPointer<Texture> texture, VertexArray<4> data);
	void end();
private:
	void generateDrawCommands();
	std::vector<unsigned short> generateIndiciesList(int quadCount);
	void lazyInit();
private:
	Shader* shader;
	glHandle vertexBuffer, textureBuffer, elementBuffer;
	std::vector<FrameData> frameData;
	std::vector<DrawCommand> drawCommands;
	int vertexBufferOffset = 0;
	int textureBufferOffset = 0;
	int currentElement = 0;
	bool isInit = false;
	int size;
};
