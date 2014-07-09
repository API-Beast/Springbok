//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <map>
#include <vector>
#include <Springbok/Parsing/UTF8.h>

#include "Image.h"
#include "Core/RenderContext2D.h"
#include "Core/Transform2D.h"

class RenderContext2D;

class BitmapFont
{
public:
	struct TextLabel
	{
		std::string String;
		BitmapFont* Font;
		template<class V = BasicVertex, class E = BasicElement>
		void prepareVertices(RenderDataPointer<V, E>& data) const;
	};
public:
	void loadCharacter(char32_t which, Image sprite);
	void loadRange(Image spriteSheet, char32_t start, char32_t end);
	void loadGrid(Image spriteSheet, char32_t start, Vec2I charSize);
	TextLabel text(const std::string& v);
public:
	std::map<char32_t, Image> LoadedCharacters;
};

template<class V, class E>
void BitmapFont::TextLabel::prepareVertices(RenderDataPointer<V, E>& data) const
{
	Vec2F offset = 0;
	int index = 0;
	Codepoint c = UTF8::DecodeAt(String, index);
	while(c)
	{
		const Image& sprite = Font->LoadedCharacters[c];
		V* oldVertex = data.Vertices;
		sprite.prepareVertices(data);
		Position2D(offset).transform(oldVertex, data.Vertices);
		offset[0] += sprite.size()[0];
		
		
		c = UTF8::DecodeNext(String, &index);
	};
}