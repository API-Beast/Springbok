//  Copyright (C) 2015 Manuel Riecke <api.beast@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "MemoryPool.h"
#include <string.h>
#include <assert.h>

MemoryPool::MemoryPool(int pageSize)
{
	PageSize = pageSize;
	appendMemoryPage();
}

bool MemoryPool::appendMemoryPage()
{
	char*  memory = new(std::nothrow) char[PageSize];
	Page*  page   = (Page*)memory;
	Block* block  = (Block*)(page+1);
	
	if(memory == nullptr)
		return false;
	 
	page->Next  = nullptr;
	block->Next = nullptr;
	block->Size = PageSize - sizeof(Page);
	
	if(!FirstPage)
		FirstPage = page;
	else
	{
		Page* lastPage = FirstPage;
		while(lastPage->Next)
			lastPage = lastPage->Next;
		lastPage->Next = page;
	}
	
	if(!FirstFreeBlock)
		FirstFreeBlock = block;
	else
	{
		Block* lastBlock = FirstFreeBlock;
		while(lastBlock->Next)
			lastBlock = lastBlock->Next;
		lastBlock->Next = block;
	}
	return true;
}

MemoryPool::~MemoryPool()
{
	Page* page = FirstPage;
	while(page)
	{
		Page* next = page->Next;
		delete[] ((char*)page);
		page = next;
	}
}

char* MemoryPool::allocateArray(int length, int elementSize)
{
	return allocate(elementSize * length);
}

void MemoryPool::freeArray(char* ptr, int length, int elementSize)
{
	return free(ptr, elementSize * length);
}

char* MemoryPool::allocateCString(const char* cstr)
{
	char* retVal = allocate(strlen(cstr)+1);
	if(!retVal)
		return retVal;
	
	strcpy(retVal, cstr);
	return retVal;
}

char* MemoryPool::allocateSubstring(const char* str, int length)
{
	char* retVal = allocate(length+1);
	if(!retVal)
		return retVal;
	
	strncpy(retVal, str, length);
	retVal[length] = 0;
	return retVal;
}

bool MemoryPool::isInPool(const char* ptr, int size) const
{
	// First check if ptr is inside a memory block.
	Page* page = FirstPage;
	while(page)
	{
		if(ptr > (char*)(page) && (ptr+size) < ((char*)(page)+PageSize))
			break;
		else
			page = page->Next;
	}
	// Then check if it is not inside one of the free areas.
	if(!page)
		return false;
	
	Block* block = FirstFreeBlock;
	while(block)
	{
		if(ptr >= (char*)(block) && ptr < ((char*)(block)+block->Size))
			break;
		block = block->Next;
	}
	return block == nullptr;
}

void MemoryPool::freeCString(const char* cstr)
{
	this->free((char*)cstr, strlen(cstr)+1);
}

char* MemoryPool::allocate(int size)
{
	Block*     block = FirstFreeBlock;
	Block* prevBlock = nullptr;
	
	// If you change this also change it in free.
	if(size < sizeof(Block))
		size = sizeof(Block);
	
	if(size > PageSize)
		return nullptr;
	
	while(block)
	{
		if(block->Size > size)
		{
			markBlockAsUsed(size, block, prevBlock);
			return (char*)block;
		}
		prevBlock = block;
		block = block->Next;
	}
	
	if(!block)
	{
		if(appendMemoryPage())
			return allocate(size);
		return nullptr;
	}
}

void MemoryPool::free(char* ptr, int size)
{
	// If you change this also change it in allocate.
	if(size < sizeof(Block))
		size = sizeof(Block);
	
	// Insert the new block
	Block* block = FirstFreeBlock;
	while(block->Next && (char*)(block->Next) < ptr)
		block = block->Next;
	
	Block* newBlock = (Block*)(ptr);
	newBlock->Size = size;
	
	if(newBlock > block)
	{
		newBlock->Next = block->Next;
		block->Next = newBlock;
	}
	else if(newBlock == block)
	{
		return; // Double free
	}
	else
	{
		FirstFreeBlock = newBlock;
		newBlock->Next = block;
	}
	
	// Now merge free blocks that are next to each other.
	block = FirstFreeBlock;
	while(block && block->Next)
	{
		if((char*)(block->Next) == ((char*)(block) + block->Size) )
		{
			block->Size += block->Next->Size;
			block->Next  = block->Next->Next;
		}
		block = block->Next;
	}
}

void MemoryPool::markBlockAsUsed(int size, Block* block, Block* prevBlock)
{
	assert((!prevBlock) || (prevBlock->Next == block));
	
	int newSize = block->Size-size;
	if(newSize > 0)
	{
		char*  nextFreeMemory = (char*)(block)+size;
		Block*       newBlock = (Block*)nextFreeMemory;
		newBlock->Next = block->Next;
		newBlock->Size = newSize;
		if(prevBlock)
			prevBlock->Next = newBlock;
		else
			FirstFreeBlock = newBlock;
	}
	else if(prevBlock)
		prevBlock->Next = block->Next;
}

int MemoryPool::countAllocatedPages() const
{
	int i = 0;
	Page* page = FirstPage;
	while(page)
	{
		i++;
		page = page->Next;
	}
	return i;
}

int MemoryPool::countFreeMemory() const
{
	int i = 0;
	Block* block = FirstFreeBlock;
	while(block)
	{
		i += block->Size;
		block = block->Next;
	}
	return i;
}

int MemoryPool::countUsedMemory() const
{
	return countAllocatedMemory() - countFreeMemory();
}

int MemoryPool::countAllocatedMemory() const
{
	return countAllocatedPages() * PageSize;
}

int MemoryPool::getPageSize() const
{
	return PageSize;
}

