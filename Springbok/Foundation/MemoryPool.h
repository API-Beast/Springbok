//  Copyright (C) 2015 Manuel Riecke <api.beast@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <new>

//~ ### MemoryPool
//~ *Dependencies: Standard headers only (string.h, assert.h, new)*
//~ 
//~ A paged memory pool with minimal allocation overhead.
//~ Paged means that once the initial capacity is full additional memory is allocated, in the same size of the initial capacity.
//~ Each page has a slight memory overhead of a single pointer. (4 bytes on 32 bit, 8 bytes on 64 bit)
struct MemoryPool
{
	//~ Initialize the MemoryPool, setting the size of a single page to *pageSize* bytes and allocating one such page.
	MemoryPool(int pageSize = 2000);
	MemoryPool(const MemoryPool& other) = delete; // We don't support copy constructing MemoryPool's at the moment.
	~MemoryPool(); // Destructing the memory pool free's all the allocated memory.
	
	//~ #### Requesting and freeing memory again.
	//~ Will return *nullptr* if the memory pool is full and no more memory.
	//~ Will also return *nullptr* if *size* is bigger than the page size passed to the constructor.
	char* allocate(int size);
	char* allocateArray(int length, int elementSize);
	//~ All memory is deallocated automatically when the destructor is called.
	//~ Marking memory as free will never cause deallocation.
	void  free(char* ptr, int size);
	void  freeArray(char* ptr, int length, int elementSize);
	
	//~ String managment
	char* allocateCString(const char* cstr);
	char* allocateSubstring(const char* str, int length);
	void  freeCString(const char* cstr);
	
	//~ Checks if *ptr* is inside a used area allocated to this pool.
	bool isInPool(const char* ptr, int size) const;
	template<typename T> bool isInPool(T* ptr) const;
	template<typename T> bool isInPoolArray(T* ptr, int length) const;
	
	//~ These templated overloads call their respective constructors and destructors.
	//~
	//~ The MemoryPool class does not keep track of what objects where constructed by it.
	//~ That means when the MemoryPool is destructed, the memory is freed but the destructors aren't called.
	//~ Keep track of your allocated objects and free them with their respective functions if it is important that their destructors are called.
	//~ Note that this is never neccessary for Plain-Old-Data types. (int, float, char*, etc.)
	template<typename T, class...Args> T* create(Args...args);
	template<typename T, class...Args> T* createArray(int i, Args...args);
	template<typename T> void free(T* ptr);
	template<typename T> void freeArray(T* ptr, int i);
	
	//~ #### Memory usage statistics.
	int countUsedMemory()      const;
	int countFreeMemory()      const;
	int countAllocatedMemory() const;
	int countAllocatedPages()  const;
	int getPageSize()          const;
	
private:
	// NOTE: Hidden complexity
	// We are avoiding as many allocations as possible in this class.
	// As such both Block and Page are never allocated seperatedly.
	// Instead they use free memory in the allocated page.
	// The page description is using the first few bytes in a allocated memory page.
	// The block description is using the first few bytes of a free block.
	//
	// That's also why both don't contain any pointer to the memory they are refering to.
	// The 'memory' pointer is the same as the 'this' pointer!
	struct Block
	{
		int    Size = 0;
	  Block* Next = nullptr;
	};
	
	struct Page
	{
		Page*  Next = nullptr;
	};
	
	void markBlockAsUsed(int size, Block* block, Block* prevBlock);
	bool appendMemoryPage();
	
	Page*  FirstPage      = nullptr;
	Block* FirstFreeBlock = nullptr;
	int    PageSize;
};

// -----------------------
// Template-Implementation
// -----------------------

template<typename T>
bool MemoryPool::isInPool(T* ptr) const
{
	return isInPool((char*)ptr, sizeof(T));
}

template<typename T>
bool MemoryPool::isInPoolArray(T* ptr, int length) const
{
	return isInPool((char*)ptr, sizeof(T)*length);
}

template<typename T, class...Args>
T* MemoryPool::create(Args...args)
{
	char* memory = this->allocate(sizeof(T));
	if(!memory)
		return nullptr;
	
	T* retVal = new(memory) T(args...);
	return retVal;
};

template<typename T, class...Args>
T* MemoryPool::createArray(int i, Args...args)
{
	char* memory = this->allocate(i * sizeof(T));
	if(!memory)
		return nullptr;
	
	int j = 0;
	while(j < i)
	{
		new(memory+j*sizeof(T)) T(args...);
		j++;
	}
	return (T*)memory;
};

template<typename T>
void MemoryPool::free(T* ptr)
{
	ptr->~T();
	this->free((char*)ptr, sizeof(T));
};

template<typename T>
void MemoryPool::freeArray(T* ptr, int i)
{
	int j = 0;
	while(j++ < i)
		(ptr++)->~T();
	this->free((char*)ptr, sizeof(T)*i);
};