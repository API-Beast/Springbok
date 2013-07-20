#pragma once

#include "../Containers/Ringbuffer.h"

template<typename T>
struct SkipListNode;

/* Low level container, API is designed to be efficient and as such it doesn't have the usual convenience of Springbok. */
template<typename T>
struct SkipList
{
	static constexpr int MaxLevel = 16;
	struct SearchResult
	{
		T Value;
		SkipListNode<T>* BaseNode = nullptr;
		RingBuffer<SkipListNode<T>*, MaxLevel> Levels;
		SkipList* List;
		
		void remove();
		void insert();
		bool hasFoundValue() const;
	};
public:
	~SkipList();
	
	SearchResult findNode(const T& value);
	
	SkipListNode<T>* Head[MaxLevel];
	int CurrentLevel = -1;
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