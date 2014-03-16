//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "List.h"
#include <Springbok/Math/Operations.h>
#include <cassert>

template<typename T>
T& List<T>::pushBack(const T& value)
{
	Version++;
	if(UsedLength >= MemoryLength)
	{
		if(AllowReallocation)
		{
			int newLength = 2;
			if(MemoryLength)
				newLength = MemoryLength * 2;
			reallocate(newLength);
		}
		else
			throw AllocatedMemoryFull();
	}
	new (Memory+(UsedLength++))T(value);
	return back();
};

template<typename T>
T List<T>::popBack()
{
	Version++;
	T retVal = Memory[--UsedLength];
	return retVal;
}

template<typename T>
T List<T>::quickRemove(int index)
{
	Version++;
	T retVal = Memory[index];
	Memory[index] = Memory[--UsedLength];
	return retVal;
}

template<typename T>
List<T>::List(int length)
{
	Memory = new T[length];
	UsedLength = 0;
	MemoryLength = length;
	OwnsMemory = true;
	AllowReallocation = true;
};

template<typename T>
List<T>::List(char* memory, int length)
{
	Memory = new(memory) T[length];
	MemoryLength = length;
	UsedLength = 0;
};

template<typename T>
List<T>::List()
{
	Memory = nullptr;
	UsedLength = MemoryLength = 0;
	OwnsMemory = false;
	AllowReallocation = true;
};

template<typename T>
List<T>::List(const std::initializer_list<T>& list)
{
	Memory = new T[list.size()];
	memMove(Memory, list.begin(), list.size());
	MemoryLength = list.size();
	UsedLength = list.size();
	OwnsMemory = true;
	AllowReallocation = true;
}

template<typename T>
List<T>::~List()
{
	if(OwnsMemory)
	{
		delete[] Memory;
		OwnsMemory = false;
	}
};

template<typename T>
List<T>::List(T* memory, int length, int usedLength)
{
	Memory = memory;
	MemoryLength = length;
	UsedLength = usedLength;
};

template<typename T>
List<T>& List<T>::operator=(const List<T>& other)
{
	if(OwnsMemory)
	{
		delete[] Memory;
		OwnsMemory = false;
	}
	Memory = new T[other.MemoryLength];
	memMove(Memory, other.Memory, other.UsedLength);
	UsedLength = other.UsedLength;
	MemoryLength = other.MemoryLength;
	OwnsMemory = true;
	AllowReallocation = true;
	return *this;
};

template<typename T>
List<T>& List<T>::operator=(List<T>&& other)
{
	if(OwnsMemory)
	{
		delete[] Memory;
		OwnsMemory = false;
	}
	Memory = other.Memory;
	UsedLength = other.UsedLength;
	OwnsMemory = other.OwnsMemory;
	MemoryLength = other.MemoryLength;
	other.OwnsMemory = false;
	AllowReallocation = other.AllowReallocation;
	return *this;
};

template<typename T>
template<int ArraySize>
List<T>::List(T (&array)[ArraySize])
{
	Memory = array;
	MemoryLength = ArraySize;
	UsedLength = ArraySize;
};

template<typename T>
void List<T>::reallocate(int elements)
{
	moveMemoryTo(new T[elements], elements);
	OwnsMemory = true;
}

template<typename T>
T& List<T>::makeSpace(int position, int elements)
{
	if((UsedLength + elements) > MemoryLength)
	{
		if(AllowReallocation)
		{
			reallocate(UsedLength + elements);
		}
		else
			throw AllocatedMemoryFull();
	}
	T* src = Memory + position;
	T* dst = Memory + position + elements;
	int size = (UsedLength - position);
	memMove(dst, src, size);
	new (src)T[elements];
	UsedLength += elements;
}

template<typename T>
T& List<T>::insert(int position, const T& value)
{
	Version++;
	if(position == UsedLength + 1)
		return pushBack(value);
	else
	{
		makeSpace(position, 1);
		return Memory[position] = value;
	}
}

template<typename T>
void List<T>::clear()
{
	*this = List<T>();
}

template<typename T>
int List<T>::findIndex(const T& value) const
{
	for(int i = 0; i < UsedLength; ++i)
		if(this->operator[](i) == value)
			return i;
	return -1;
}

template<typename T>
void List<T>::moveMemoryTo(T* memory, int length)
{
	if(UsedLength < length)
		memMove(memory, Memory, UsedLength);
	else
		memMove(memory, Memory, length);
	
	if(OwnsMemory)
		delete[] Memory;
	
	Memory = memory;
	MemoryLength = length;
}

template<typename T>
void List<T>::memMove(T* dst, const T* src, int length)
{
	if(length)
	{
		T* copy = new T[length*sizeof(T)];
		for(int i = 0; i < length; ++i)
		{
			(copy+i)->~T();
			new (copy+i)T(*(src+i));
		}
		for(int i = 0; i < length; ++i)
			new (dst+i)T(*(copy+i));
		delete[] copy;
	}
}

template <typename T, typename C, C T::*Member>
int Map<T,C,Member>::findIndex(const C& searchFor, int minmin, int maxmax, int prevMid) const
{
	int min = minmin;
	int max = maxmax;
	int mid = (min + ((max-min) / 2));

	if(min >= max)
	{
		min = Max(mid - 1, 0);
		max = Min(mid + 1, Data.UsedLength-1);
		
		if(searchFor < Data[min].*Member)
			return min-1;
		
		int i = min;
		while(i < max)
		{
			const C& value  = Data[i].*Member;
			const C& valueB = Data[i+1].*Member;
			if(value == searchFor)
				return i;
			if(value < searchFor)
				if(valueB > searchFor)
					return i;
			i++;
		}
		
		return max;
	}
	
	const C& value = Data[mid].*Member;
	if(value > searchFor)
		return findIndex(searchFor, min, mid-1, mid);
	if(value < searchFor)
		return findIndex(searchFor, mid+1, max, mid);
	return mid;
}

template <typename T, typename C, C T::*Member>
int Map<T,C,Member>::findIndex(const C& index) const
{
	if(Data.Memory == nullptr)
		return 0;
	return findIndex(index, 0, Data.UsedLength - 1, 0);
};

template <typename T, typename C, C T::*Member>
T& Map<T,C,Member>::operator[](const C& index)
{
	int i = findIndex(index);
	if(i < Data.UsedLength && i >= 0)
		if(Data[i].*Member == index)
			return Data[i];
	
	T t{};
	t.*Member = index;
	return Data.insert(i+1, t);
}

template <typename T, typename C, C T::*Member>
T Map<T,C,Member>::operator[](const C& index) const
{
	int i = findIndex(index);
	if(i < Data.UsedLength && i >= 0)
		if(Data[i].*Member == index)
			return Data[i];
	return T();
}

template <typename T, typename C, C T::*Member>
T& Map<T,C,Member>::insert(const T& t)
{
	if(!Data.Memory)
		return Data.insert(0, t);
	int i = findIndex(t.*Member);
	return Data.insert(i+1, t);
}

template <typename T, typename C, C T::*Member>
void Map<T,C,Member>::sort()
{
	for (int i = 1; i < Data.UsedLength; ++i)
	{
		T temp = Data[i];
		int j = i -1;
		
		while((j >= 0) && (Data[j].*Member > temp.*Member))
		{
			Data[j + 1] = Data[j];
			j--;
		}
		
		Data[j+1] = temp;
	}
}