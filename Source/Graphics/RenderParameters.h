#pragma once
#include <Source/Geometry/Vec2.h>
#include <Source/Geometry/Angle.h>

struct RenderParameters
{
	RenderParameters() {};
	RenderParameters(Vec2I pos) : RenderParameters(pos,this->Rotation) {};
	RenderParameters(Vec2I pos, Angle rotation) : RenderParameters(pos,rotation,this->Scale) {};
	RenderParameters(Vec2I pos, Angle rotation, Vec2F scale) : RenderParameters(pos,rotation,scale,this->Alignment) {};
	RenderParameters(Vec2I pos, Angle rotation, Vec2F scale, Vec2F alignment) : RenderParameters(pos,rotation,scale,alignment,this->Parallaxity) {};
	RenderParameters(Vec2I pos, Angle rotation, Vec2F scale, Vec2F alignment, Vec2F parallaxity);
	
	RenderParameters(int x, int y);
	RenderParameters(int x, int y, Angle rotation);
	RenderParameters(int x, int y, Angle rotation, int scaleX, int scaleY);
	RenderParameters(int x, int y, Angle rotation, int scaleX, int scaleY, int alignX, int alignY);
	RenderParameters(int x, int y, Angle rotation, int scaleX, int scaleY, int alignX, int alignY, int parallaxX, int parallaxY);
	
	RenderParameters(const RenderParameters& parent);
	
	RenderParameters operator+(const RenderParameters& other) const;
	RenderParameters operator-(const RenderParameters& other) const;
	
	Vec2I Offset      = Vec2I(0, 0);
	Vec2F Scale       = Vec2F(+1.0f, +1.0f);
	Vec2F Alignment   = Vec2F(+0.5f, +0.5f);
	Vec2F Parallaxity = Vec2F(1, 1);
	Angle Rotation    = 0.0_turn;
};