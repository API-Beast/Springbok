#include "RenderParameters.h"

RenderParameters::RenderParameters(Vec2I pos, Angle rotation, Vec2F scale, Vec2F alignment, Vec2F parallaxity)
{
	this->Offset = pos;
	this->Rotation = rotation;
	this->Scale = scale;
	this->Alignment = alignment;
	this->Parallaxity = parallaxity;
}

RenderParameters::RenderParameters(int x, int y)
{
	this->Offset = Vec2I(x,y);
}

RenderParameters::RenderParameters(int x, int y, Angle rotation)
{
	this->Offset = Vec2I(x,y);
	this->Rotation = rotation;
}

RenderParameters::RenderParameters(int x, int y, Angle rotation, int scaleX, int scaleY)
{
	this->Offset = Vec2I(x,y);
	this->Rotation = rotation;
	this->Scale = Vec2F(scaleX, scaleY);
}

RenderParameters::RenderParameters(int x, int y, Angle rotation, int scaleX, int scaleY, int alignX, int alignY)
{
	this->Offset = Vec2I(x,y);
	this->Rotation = rotation;
	this->Scale = Vec2F(scaleX, scaleY);
	this->Alignment = Vec2F(alignX,alignY);
}

RenderParameters::RenderParameters(int x, int y, Angle rotation, int scaleX, int scaleY, int alignX, int alignY, int parallaxX, int parallaxY)
{
	this->Offset = Vec2I(x,y);
	this->Rotation = rotation;
	this->Scale = Vec2F(scaleX, scaleY);
	this->Alignment = Vec2F(alignX,alignY);
	this->Parallaxity = Vec2F(parallaxX,parallaxY);
}

RenderParameters::RenderParameters(const RenderParameters& parent)
{
	this->Offset = parent.Offset;
	this->Rotation = parent.Rotation;
	this->Scale = parent.Scale;
	this->Alignment = parent.Alignment;
	this->Parallaxity = parent.Parallaxity;
}

RenderParameters RenderParameters::operator+(const RenderParameters& other) const
{
	return RenderParameters(this->Offset + other.Offset, this->Rotation + other.Rotation, this->Scale + other.Scale, this->Alignment + other.Alignment, this->Parallaxity + other.Parallaxity);
}

RenderParameters RenderParameters::operator-(const RenderParameters& other) const
{
	return RenderParameters(this->Offset - other.Offset, this->Rotation - other.Rotation, this->Scale - other.Scale, this->Alignment - other.Alignment, this->Parallaxity - other.Parallaxity);
}