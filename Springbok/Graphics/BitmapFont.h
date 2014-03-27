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
	struct Glyph
	{
		char32_t Codepoint;
		Image Sprite;
	};
public:
	void loadCharacter(char32_t which, Image sprite);
	void loadRange(Image spriteSheet, char32_t start, char32_t end);
	void loadGrid(Image spriteSheet, char32_t start, Vec2I charSize);
	
	template<class V = BasicVertex, class E = BasicElement, class C = char>
	void prepareVertices(RenderDataPointer<V, E>& data, const std::basic_string<C>& str) const;
public:
	Map<Glyph, char32_t, &Glyph::Codepoint> LoadedCharacters;
};

template<class V, class E, class C>
void BitmapFont::prepareVertices(RenderDataPointer<V, E>& data, const std::basic_string<C>& str) const
{
	Vec2F offset = 0;
	for(const auto& c : str)
	{
		const Image& sprite = LoadedCharacters[c].Sprite;
		V* oldVertex = data.Vertices;
		sprite.prepareVertices(data);
		Position2D(offset).transform(oldVertex, data.Vertices);
		offset[0] += sprite.getSize()[0];
	}	
}