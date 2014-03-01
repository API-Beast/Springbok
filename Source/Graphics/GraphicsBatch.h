#pragma once

#include <Springbok/Containers/VertexArray.h>
#include <Springbok/Generic/ObjectPointer.h>
#include "GLTypes.h"
#include "Texture.h"
#include <vector>

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

class GraphicsBatch
{
public:
	GraphicsBatch(int size = 256);
public:
	void start();
	void draw(ObjectPointer<Texture> texture, VertexArray<4> data);
	void end();
private:
	void lazyInit();
private:
	Shader* shader;
	glHandle vertexBuffer, textureBuffer;
	std::vector<FrameData> frameData;
	int vertexBufferOffset = 0;
	int textureBufferOffset = 0;
	int currentElement = 0;
	bool isInit = false;
	int size;
};
