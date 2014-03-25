//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <Springbok/Geometry/Vec2.h>
#include <Springbok/Geometry/Angle.h>
#include "VertexStruct.h"
#include <Springbok/Utils/Debug.h>

struct Transform2D
{
	Transform2D() = default;
	Transform2D(Vec2I pos, Angle rotation = 0.0_turn, Vec2F scale = 1, Vec2F alignment = 0.5f, Vec2F parallaxity = 1.f);
	Transform2D(Vec2I pos, Vec2F scale, Vec2F alignment = 0.5f, Vec2F parallaxity = 1.f);
	
	template<class V = BasicVertex>
 	void transform(V* startVertex, V* endVertex, Vec2F cameraPos = 0, Vec2F coordinateMult = 1) const;
	
	Transform2D operator+(const Transform2D& other) const;
	Transform2D operator-(const Transform2D& other) const;
	
	Vec2I Offset       = 0;
	Vec2F Scale        = 1;
	Vec2F Alignment    = 0.5f;
	Angle Rotation     = 0.0_turn;
	Vec2F Parallaxity  = 1.f;
};

inline Transform2D  Position2D(Vec2F pos  ){ return Transform2D(pos);                    };
inline Transform2D PositionGUI(Vec2F pos  ){ return Transform2D(pos, 1, 0.5f, 0.0f);     }; // Render without Camera influence
inline Transform2D     Scale2D(Vec2F size ){ return Transform2D(0,   size);              };
inline Transform2D     Align2D(Vec2F align){ return Transform2D(0,   1, align);          };
inline Transform2D  Parallax2D(Vec2F paral){ return Transform2D(0,   1, 0.5f, paral);    };
inline Transform2D    Rotate2D(Angle rot  ){ return Transform2D(0,   rot);               };

inline Transform2D  Position2D(float v0, float v1){ return  Position2D(Vec2F(v0, v1)); };
inline Transform2D PositionGUI(float v0, float v1){ return PositionGUI(Vec2F(v0, v1)); }; // Render without Camera influence
inline Transform2D     Scale2D(float v0, float v1){ return     Scale2D(Vec2F(v0, v1)); };
inline Transform2D     Align2D(float v0, float v1){ return     Align2D(Vec2F(v0, v1)); };
inline Transform2D  Parallax2D(float v0, float v1){ return  Parallax2D(Vec2F(v0, v1)); };

#include "Transform2D_Templates.hpp"