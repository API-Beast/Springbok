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
	
	template<class T>
	struct TextLabel
	{
		T String;
		BitmapFont* Font;
		template<class V = BasicVertex, class E = BasicElement>
		void prepareVertices(RenderDataPointer<V, E>& data) const;
	};
public:
	void loadCharacter(char32_t which, Image sprite);
	void loadRange(Image spriteSheet, char32_t start, char32_t end);
	void loadGrid(Image spriteSheet, char32_t start, Vec2I charSize);
	template<class T>
	TextLabel<T> text(T v)
	{
		return TextLabel<T>{v, this};
	};
public:
	Map<Glyph, char32_t, &Glyph::Codepoint> LoadedCharacters;
};

template<class T>
template<class V, class E>
void BitmapFont::TextLabel<T>::prepareVertices(RenderDataPointer<V, E>& data) const
{
	Vec2F offset = 0;
	for(const auto& c : String)
	{
		const Image& sprite = Font->LoadedCharacters[c].Sprite;
		V* oldVertex = data.Vertices;
		sprite.prepareVertices(data);
		Position2D(offset).transform(oldVertex, data.Vertices);
		offset[0] += sprite.getSize()[0];
	}	
}