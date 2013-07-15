#pragma once

#include "../Containers/Ringbuffer.h"

template<typename T>
struct SkipListNode;

template<typename T>
struct SkipList
{
	~SkipList();
	
	SkipListNode<T>* find(const T& value);
	SkipListNode<T>* insert(const T& value);
	
	// 10 levels should be sufficient for up to 22k elements. log(22000) < 10
	static constexpr int MaxLevel = 10;
	SkipListNode<T>* Head[MaxLevel];
	SkipListNode<T>* Tail = nullptr;
	int CurrentLevel = -1;
private:
	SkipListNode<T>* find(const T& value, RingBuffer< SkipListNode< T >*, MaxLevel >& levels);
};

template<typename T>
struct SkipListNode
{
	SkipListNode(){};
	SkipListNode(const T& val) : IsBaseNode(true), Data(val){};
	SkipListNode(SkipListNode<T>* child) : Child(child)
	{
		if(child->IsBaseNode)
			BaseChild = child;
		else
			BaseChild = Child->BaseChild;
	};
	
	SkipListNode<T>* Previous = nullptr;
	SkipListNode<T>* Next = nullptr;
	
	const T& getData();
	
	bool IsBaseNode = false;
	union
	{
		struct // Non-Base Node
		{
			SkipListNode<T>* Child     = nullptr;
			SkipListNode<T>* BaseChild;
			// For quickly accessing Data, could also be get by
			// while(BaseChild->Child){ BaseChild = BaseChild }
		};
		struct // Base Node
		{
			T Data;
		};
	};
};

#include "SkipList_Templates.hpp"