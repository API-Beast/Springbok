//  Copyright (C) 2015 Manuel Riecke <api.beast@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "MemoryPool.h"
#include <cinttypes>
#include <utility>

template<typename K, typename V>
struct HashTable
{
	using HashFn_t = uint32_t (*)(const K&);
	struct Entry;
	
	HashTable(HashFn_t hashFunction, int initialSize = 128, MemoryPool* pool = nullptr);
	HashTable(HashTable&& other);
	~HashTable();
	HashTable& operator=(HashTable&& other);
	
	V&     insert(const K& key, const V& value); // Note: This will always insert, independent of wheter the key already exists or not.
	V*     get(const K& key);
	Entry* find(const K& key); // Returns a single-linked-list-entry with a "nextWithSameKey" method and Key and Value members.
	
	V&     getOrInsert(const K& key, const V& value=V());
	V&     operator[](const K& key){ return getOrInsert(key); };
	
	// We are not automatically rehashing. Decide for yourself when to do that.
	void rehash(int length);
	int  countHashCollisions() const;
	
	
	// Members
	Entry**     Buckets    = nullptr;
	int         NumBuckets = 0;
	HashFn_t    HashFn     = nullptr;
	
	// Memory managment
	MemoryPool* Pool       = nullptr;
	bool        OwnsPool   = false;
	
	// Statistics
	// Only incremented internally, no logic depends on this though.
	int ElementCount = 0;
	// TODO: More statistics to give more flexibility on deciding when to rehash the table?
	
	
	struct Entry
	{
		Entry(const K& k, const V& v):Key(k),Value(v){};
		K Key;
		V Value;
		Entry* Next = nullptr;
		Entry* nextWithSameKey();
	};
};





/////////////////////
// Implementation  //
/////////////////////


template<typename K, typename V>
HashTable<K,V>::HashTable(HashFn_t hashFunction, int initialSize, MemoryPool* pool) : HashFn(hashFunction)
{
	if(pool)
	{
		Pool = pool;
		OwnsPool = false;
	}
	else
	{
		Pool = new MemoryPool((initialSize*sizeof(Entry*)*4)+8);
		OwnsPool = true;
	}
	
	NumBuckets = initialSize;
	Buckets = Pool->createArray<Entry*>(initialSize, nullptr);
};

template<typename K, typename V>
HashTable<K,V>::~HashTable()
{
	if(OwnsPool)
		delete Pool;
	else if(Pool->isInPoolArray(Buckets, NumBuckets))
	{
		for(int i = 0; i < NumBuckets; i++)
		{
			Entry* entry = Buckets[i];
			Entry* nextEntry = nullptr;
			while(entry)
			{
				nextEntry = entry->Next;
				Pool->free(entry);
				entry = nextEntry;
			}
		}
		Pool->freeArray(Buckets, NumBuckets);
	}
};

template<typename K, typename V>
HashTable<K,V>::HashTable(HashTable<K,V>&& other)
{
	(*this) = other;
}

template<typename K, typename V>
HashTable<K,V>& HashTable<K,V>::operator=(HashTable<K,V>&& other)
{
	Pool = other.Pool;
	OwnsPool = other.OwnsPool;
	Buckets = other.Buckets;
	NumBuckets = other.NumBuckets;
	HashFn = other.HashFn;
	ElementCount = other.ElementCount;
	
	other.OwnsPool = false;
	other.Buckets = nullptr;
	other.NumBuckets = 0;
	return *this;
};

template<typename K, typename V>
void HashTable<K,V>::rehash(int length)
{
	HashTable newTable(HashFn, length, Pool);
	
	for(int i = 0; i < NumBuckets; i++)
	{
		Entry* entry = Buckets[i];
		while(entry)
		{
			newTable.insert(entry->Key, entry->Value);
			entry = entry->Next;
		}
	}
	
	bool ownedPool = OwnsPool;
	OwnsPool = false;
	this->~HashTable();
	(*this) = std::move(newTable);
	OwnsPool = ownedPool;
};

template<typename K, typename V>
V& HashTable<K,V>::insert(const K& key, const V& value)
{
	int bucket = HashFn(key) % NumBuckets;
	
	Entry* newEntry = Pool->create<Entry>(key, value);
	Entry* oldEntry = Buckets[bucket];
	
	Buckets[bucket] = newEntry;
	newEntry->Next = oldEntry;
	
	ElementCount++;
	
	return newEntry->Value;
};

template<typename K, typename V>
typename HashTable<K,V>::Entry* HashTable<K,V>::find(const K& key)
{
	int bucket = HashFn(key) % NumBuckets;
	
	Entry* entry = Buckets[bucket];
	while(entry)
	{
		if(entry->Key == key)
			return entry;
		entry = entry->Next;
	}
	return nullptr;
}

template<typename K, typename V>
V* HashTable<K,V>::get(const K& key)
{
	Entry* entry = this->find(key);
	if(entry)
		return &(entry->Value);
	return nullptr;
}

template<typename K, typename V>
V& HashTable<K,V>::getOrInsert(const K& key, const V& value)
{
	int bucket = HashFn(key) % NumBuckets;
	
	Entry* entry = Buckets[bucket];
	while(entry)
	{
		if(entry->Key == key)
			return entry->Value;
		entry = entry->Next;
	}
	
	Entry* newEntry = Pool->create<Entry>(key, value);
	Entry* oldEntry = Buckets[bucket];
	Buckets[bucket] = newEntry;
	newEntry->Next = oldEntry;
	ElementCount++;
	return newEntry->Value;
}

template<typename K, typename V>
typename HashTable<K,V>::Entry* HashTable<K,V>::Entry::nextWithSameKey()
{
	Entry* next = this->Next;
	while(true)
	{
		if(next == nullptr)
			return nullptr;
		if(next->Key == this->Key)
			return next;
		next = next->next;
	}
}

template<typename K, typename V>
int HashTable<K,V>::countHashCollisions() const
{
	int numHashCollisions = 0;
	for(int i = 0; i < NumBuckets; i++)
	{
		K*  keys[64];
		int numKeys = 0;
		
		Entry* entry = Buckets[i];
		while(entry)
		{
			bool isInKeys = false;
			int j = 0;
			while(j < numKeys)
			if(*(keys[j++]) == entry->Key)
			{
				isInKeys = true;
				break;
			}
			
			if(!isInKeys)
			{
				keys[numKeys] = &(entry->Key);
				numKeys++;
				if(numKeys == 64)
					break;
			}
			
			entry = entry->Next;
		}
		
		if(numKeys)
			numHashCollisions += (numKeys-1);
	}
	return numHashCollisions;
}
