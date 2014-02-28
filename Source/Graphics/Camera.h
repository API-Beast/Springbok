#pragma once

#include <Springbok/Geometry/Rect.h>
#include <Springbok/Containers/VertexArray.h>

class Camera
{
public:
	Camera(int width, int height);
public:
	VertexArray<4> transformRect(RectF rect);
private:
	int width, height;
};
