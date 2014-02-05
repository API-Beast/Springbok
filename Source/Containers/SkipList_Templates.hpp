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
void SkipList<T>::SearchResult::insert()
{
	// No element in this SkipList yet? Well, congratulations.
	if(BaseNode == nullptr)
	{
		List->CurrentLevel = 0;
		SkipListNode<T>* newNode = new SkipListNode<T>(Value);
		List->Head[0] = newNode;
		
		BaseNode = newNode;
	}
	else
	{
		// This might seem weird but is required to make SkipList work as associative array.
		if(BaseNode->Data == Value)
		{
			BaseNode->Data = Value;
			return;
		}
		
		SkipListNode<T>* newNode = new SkipListNode<T>(Value);
		SkipListNode<T>* after   = BaseNode->Next;
		BaseNode->Next = newNode;
		newNode->Previous = BaseNode;
		newNode->Next     = after;
		
		BaseNode = newNode;
		
		// TODO: Insert higher levels. That's what we need the levels variable for.
		return;
	}
}

template<typename T>
typename SkipList<T>::SearchResult SkipList<T>::findNode(const T& value)
{
	SearchResult result;
	result.Value = value;
	result.List = this;
	if(CurrentLevel == -1)
		return result;
	
	SkipListNode<T>* curNode  = Head[CurrentLevel];
	SkipListNode<T>* lastNode = curNode;
	while(1)
	{
		while(curNode->getData() < value)
		{
			if(curNode->Next == nullptr)
			{
				if(curNode->IsBaseNode)
					result.BaseNode = curNode;
				else
					result.BaseNode = curNode->BaseChild;
				return result;
			}
			
			lastNode = curNode;
			curNode = curNode->Next;
		}
		if(lastNode->IsBaseNode)
		{
			if(curNode->getData() == value)
				result.BaseNode = curNode;
			else
				result.BaseNode = lastNode;
			return result;
		}
		result.Levels.pushBack(lastNode);
		curNode = lastNode->Child;
	}
	return result;
}

template<typename T>
const T& SkipListNode<T>::getData()
{
	if(IsBaseNode)
		return Data;
	return BaseChild->Data;
}


template<typename T>
bool SkipList<T>::SearchResult::hasFoundValue() const
{
	if(BaseNode == nullptr) return false;
	return BaseNode->Data == Value;
}
