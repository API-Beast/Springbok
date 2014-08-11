//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "Vec2.h"

struct MemoryBlock
{
	unsigned char* DataPtr    = nullptr;
	bool  Autonomous = false;
	
	int   UsedBytes     = 0;
	int   ReservedBytes = 0;
	
	void fill(int value);
	
	MemoryBlock(){};
	// Preallocated (memory owned by something else)
	MemoryBlock(unsigned char* memory, int length, int used = 0);
	// Dynamic & Autonomous (memory owned by MemoryBlock instance itself)
	MemoryBlock(int length);
	
	MemoryBlock(MemoryBlock&& other);
	MemoryBlock(const MemoryBlock& other);
	
	virtual ~MemoryBlock();
};