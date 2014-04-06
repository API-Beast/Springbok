//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "BitmapFont.h"

void BitmapFont::loadCharacter(char32_t which, Image sprite)
{
	LoadedCharacters[which].Sprite = sprite;
}

void BitmapFont::loadRange(Image spriteSheet, char32_t start, char32_t end)
{
	int width = spriteSheet.size().X;
	int height = spriteSheet.size().Y;
	int numChar = (end - start) + 1;
	int widthPerChar = width / numChar;
	for(int i = 0; i < numChar; ++i)
		LoadedCharacters[start + i].Sprite = spriteSheet.cut(Vec2I(widthPerChar*i, 0), Vec2I(widthPerChar, height));
}

void BitmapFont::loadGrid(Image spriteSheet, char32_t start, Vec2I charSize)
{
	int maxRow = spriteSheet.size().X / charSize.X;
	int maxCollumn = spriteSheet.size().Y / charSize.Y;
	for(int collumn = 0; collumn < maxCollumn; ++collumn)
		for(int row = 0; row < maxRow; ++row)
		{
			int index = start + collumn * maxRow + row;
			LoadedCharacters[index].Sprite = spriteSheet.cut(Vec2I(row, collumn)*charSize, charSize);
		}
}