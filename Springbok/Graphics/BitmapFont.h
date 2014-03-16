//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once
#include <Springbok/Containers/List.h>
#include "Image.h"
#include "RenderContext.h"

class RenderContext;

class BitmapFont
{
public:
	struct Char
	{
		char32_t Codepoint;
		Image Sprite;
	};
public:
	void loadCharacter(char32_t which, Image sprite);
	void loadRange(Image spriteSheet, char32_t start, char32_t end);
	void loadGrid(Image spriteSheet, char32_t start, Vec2I charSize);
	
	template<class V = BasicVertex, class U = BasicUniforms>
	VertexArray<V, U> prepareVertices() const;
public:
	Map<Char, char32_t, &Char::Codepoint> LoadedCharacters;
};