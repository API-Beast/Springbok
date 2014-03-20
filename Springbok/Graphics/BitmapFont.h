//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once
#include <Springbok/Containers/List.h>
#include "Image.h"
#include "RenderContext2D.h"
#include "Transform2D.h"

class RenderContext2D;

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
	
	template<class V = BasicVertex, class U = BasicElement>
	void prepareVertices(V*& vertices, U*& elements, const std::u32string& str) const;
public:
	Map<Char, char32_t, &Char::Codepoint> LoadedCharacters;
};

template<class V, class U>
void BitmapFont::prepareVertices(V*& vertices, U*& elements, const std::u32string& str) const
{
	Vec2F offset = 0;
	for(const auto& c : str)
	{
		Image& sprite = LoadedCharacters[c].Sprite;
		int preparedElements = sprite.prepareVertices(vertices, elements);
		Transform2D(offset).transform(vertices, elements, preparedElements);
		offset[0] += sprite.getSize()[0];
	}	
}