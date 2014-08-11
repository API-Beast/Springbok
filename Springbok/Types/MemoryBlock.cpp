//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "MemoryBlock.h"

#include <cstdlib>

MemoryBlock::MemoryBlock(int length)
{
	DataPtr       = (unsigned char*)std::malloc(length);
	Autonomous    = true;
	UsedBytes     = 0;
	ReservedBytes = length;
}

MemoryBlock::MemoryBlock(unsigned char* memory, int length, int used)
{
	DataPtr       = memory;
	Autonomous    = false;
	ReservedBytes = length;
	UsedBytes     = used;
}

MemoryBlock::~MemoryBlock()
{
	if(Autonomous)
		std::free(DataPtr);
}

MemoryBlock::MemoryBlock(MemoryBlock&& other)
{
	DataPtr       = other.DataPtr;
	UsedBytes     = other.UsedBytes;
	ReservedBytes = other.ReservedBytes;
	
	Autonomous = other.Autonomous;
	other.Autonomous = false;
}

MemoryBlock::MemoryBlock(const MemoryBlock& other)
{
	DataPtr       = other.DataPtr;
	UsedBytes     = other.UsedBytes;
	ReservedBytes = other.ReservedBytes;
	Autonomous    = false;
}

void MemoryBlock::fill(int value)
{
	for(int* it = (int*)DataPtr; it < (int*)(DataPtr+ReservedBytes); ++it)
		*it = value;
}