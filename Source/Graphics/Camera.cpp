#include "Camera.h"
#include <array>

Camera::Camera(int width, int height)
{
	this->width = width;
	this->height = height;
}

VertexArray<4> Camera::transformRect(RectF rect)
{
	VertexArray<4> output;
	
	int halfWidth = width / 2;
	int halfHeight = height / 2;
	float xPixelFactor = 1.0f / halfWidth;
	float yPixelFactor = 1.0f / halfHeight;
	
	Vec2F origin = rect.getOrigin();
	Vec2F size = rect.getSize();
	
	output[0] = Vec2F((xPixelFactor * (origin.X)) - 1.0f, (yPixelFactor * (origin.Y)) - 1.0f);
	output[1] = Vec2F((xPixelFactor * (origin.X + size.X)) - 1.0f, (yPixelFactor * (origin.Y)) - 1.0f);
	output[2] = Vec2F((xPixelFactor * (origin.X)) - 1.0f, (yPixelFactor * (origin.Y + size.Y)) - 1.0f);
	output[3] = Vec2F((xPixelFactor * (origin.X + size.X)) - 1.0f, (yPixelFactor * (origin.Y + size.Y)) - 1.0f);
	
	/*
	 * 	output[0] = Vec2F(xPixelFactor * ((origin.X) - 0.5f), yPixelFactor * ((origin.Y) - 0.5f));
	output[1] = Vec2F(xPixelFactor * ((origin.X + size.X) - 0.5f), yPixelFactor * ((origin.Y) - 0.5f));
	output[2] = Vec2F(xPixelFactor * ((origin.X) - 0.5f), yPixelFactor * ((origin.Y + size.Y) - 0.5f));
	output[3] = Vec2F(xPixelFactor * ((origin.X + size.X) - 0.5f), yPixelFactor * ((origin.Y + size.Y) - 0.5f));
	 * */
	
	return output;
}
