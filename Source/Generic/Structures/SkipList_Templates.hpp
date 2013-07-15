#pragma once

#include "SkipList.h"

template<typename T>
SkipList<T>::~SkipList()
{
	for(int i=0; i < CurrentLevel; i++)
	{
		SkipListNode<T>* curNode = Head[i];
		SkipListNode<T>* lastNode;
		while(curNode)
		{
			lastNode = curNode;
			curNode = curNode->Next;
			delete lastNode;
		}
	}
}

template<typename T>
SkipListNode<T>* SkipList<T>::insert(const T& value)
{
	RingBuffer<SkipListNode<T>*, MaxLevel> levels;
	SkipListNode<T>* insertPosition = find(value, levels);
	
	// No element in this SkipList yet? Well, congratulations.
	if(insertPosition == nullptr)
	{
		CurrentLevel = 0;
		SkipListNode<T>* newNode = new SkipListNode<T>(value);
		Head[CurrentLevel] = newNode;
		Tail = newNode;
	}
	else
	{
		// This might seem weird but is required to make SkipList work as associative array.
		if(insertPosition->Data == value)
		{
			insertPosition->Data = value;
			return insertPosition;
		}
		
		SkipListNode<T>* newNode = new SkipListNode<T>(value);
		SkipListNode<T>* after   = insertPosition->Next;
		insertPosition->Next = newNode;
		newNode->Previous = insertPosition;
		newNode->Next     = after;
		
		if(Tail == insertPosition)
			Tail = newNode;
		// TODO: Insert higher levels. That's what we need the levels variable for.
		return newNode;
	}
}

template<typename T>
SkipListNode<T>* SkipList<T>::find(const T& value)
{
	RingBuffer<SkipListNode<T>*, MaxLevel> levels;
	return find(value, levels);
}

template<typename T>
SkipListNode<T>* SkipList<T>::find(const T& value, RingBuffer<SkipListNode<T>*, MaxLevel>& levels)
{
	if(CurrentLevel == -1)
		return nullptr; // This Skiplist has no values yet
	
	SkipListNode<T>* curNode  = Head[CurrentLevel];
	SkipListNode<T>* lastNode = curNode;
	while(1)
	{
		while(curNode->getData() < value)
		{
			if(curNode->Next == nullptr)
				return Tail;
			
			lastNode = curNode;
			curNode = curNode->Next;
		}
		if(lastNode->IsBaseNode)
			return lastNode;
		levels.pushBack(lastNode);
		curNode = lastNode->Child;
	}
}

template<typename T>
const T& SkipListNode<T>::getData()
{
	if(IsBaseNode)
		return Data;
	return BaseChild->Data;
}
