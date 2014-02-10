//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <initializer_list>

struct AllocatedMemoryFull{};

template <typename T>
class List
{
public:
	List(T* memory, int length, int used=0);
	List(char* memory, int length);
	template<int ArraySize>
	List(T (&array)[ArraySize]);
	List(int length);
	List(const std::initializer_list<T>& list);
	List();
	~List();
	
	T& operator[](int index){ return *(Memory+index); };
	T& pushBack(const T& value);
	T   popBack();
	
	T&  back(int i=0){ return operator[](UsedLength - 1 - i); };
	T& front(int i=0){ return operator[](i); };
	
	T* begin(){ return Memory; };
	T*   end(){ return Memory+UsedLength; };
	
	T quickRemove(int index); /// Changes element order
	
	void moveMemoryTo(T* memory, int length);
	void reallocate(int elements);
	
	T& insert(int position, const T& value);
	T& makeSpace(int position, int elements=1);
protected:
	void memMove(T* dst, const T* src, int length);
public:
	bool OwnsMemory = false;
	bool AllowReallocation = false;
	T* Memory = nullptr;
	int MemoryLength = 0;
	int UsedLength = 0;
};

/** A @ref List that is assumed to be sorted by \a Member of \a T and thus can search for a specific key value in logarithmic time.  */
template <typename T, typename C, C T::*Member>
class Map
{
public:
	/** Constructor, data will get sorted. */
	Map(const std::initializer_list<T>& list) : Data(list) { sort(); };
	Map(T* memory, int length, int used=0) : Data(memory, length, used){ sort(); };
	template<int ArraySize>
	Map(T (&array)[ArraySize]) : Data(array) { sort(); };
	Map(int length) : Data(length){};
	Map() : Data(){};
	T& operator[](const C& item);
	template<typename X, X T::*member>
	void findBy(const X& item){};
	T& insert(const T& t);
	void sort();
protected:
	int findIndex(const C& item);
public:
	List<T> Data;
};

#include "List_Templates.hpp"