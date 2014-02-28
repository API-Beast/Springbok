#pragma once

#include "Springbok/Containers/VertexArray.h"
#include "GLTypes.h"
#include <stack>

class Shader;

class GraphicsBatch
{
public:
	GraphicsBatch(int size = 256);
public:
	void Start();
	void Draw(VertexArray<4> data);
	void End();
private:
	void lazyInit();
private:
	Shader* shader;
	glHandle vertexBuffer, textureBuffer;
	std::stack<VertexArray<4>> frameData;
	int bufferOffset = 0;
	bool isInit = false;
	int size;
};
