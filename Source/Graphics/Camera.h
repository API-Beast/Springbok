#pragma once
#include <Source/Geometry/Rect.h>
#include <array>

class Camera
{
public:
	Camera(int width, int height);
public:
	std::array<Vec2F,4> transformRect(RectF rect);
private:
	int width, height;
};