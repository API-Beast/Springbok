#include "SimpleList.h"
#pragma once

template<typename T>
T& SimpleList<T>::pushBack(const T& value)
{
	if(UsedLength >= MemoryLength)
	{
		if(AllowReallocation)
			reallocate((UsedLength * 2) || 2);
		else
			throw AllocatedMemoryFull();
	}
	new (Memory+(UsedLength++))T(value);
};

template<typename T>
T SimpleList<T>::popBack()
{
	T retVal = Memory[--UsedLength];
	return retVal;
}

template<typename T>
SimpleList<T>::SimpleList(int length)
{
	Memory = new T[length];
	UsedLength = MemoryLength = length;
	OwnsMemory = true;
	AllowReallocation = true;
};

template<typename T>
SimpleList<T>::SimpleList(char* memory, int length)
{
	Memory = new(memory) T[length];
	MemoryLength = length;
	UsedLength = 0;
};

template<typename T>
SimpleList<T>::SimpleList()
{
	Memory = nullptr;
	UsedLength = MemoryLength = 0;
	OwnsMemory = false;
	AllowReallocation = true;
};

template<typename T>
SimpleList<T>::SimpleList(const std::initializer_list<T>& list)
{
	Memory = new T[list.size()];
	memMove(Memory, list.begin(), list.size());
	UsedLength = list.size();
	OwnsMemory = true;
	AllowReallocation = true;
}

template<typename T>
SimpleList<T>::~SimpleList()
{
	if(OwnsMemory)
		delete[] Memory;
};

template<typename T>
SimpleList<T>::SimpleList(T* memory, int length, int usedLength)
{
	Memory = memory;
	MemoryLength = length;
	UsedLength = usedLength;
};

template<typename T>
template<int ArraySize>
SimpleList<T>::SimpleList(T (&array)[ArraySize])
{
	Memory = array;
	MemoryLength = ArraySize;
	UsedLength = ArraySize;
};

template<typename T>
void SimpleList<T>::reallocate(int elements)
{
	moveMemoryTo(new T[elements], elements);
	OwnsMemory = true;
}

template<typename T>
T& SimpleList<T>::makeSpace(int position, int elements)
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
T& SimpleList<T>::insert(int position, const T& value)
{
	makeSpace(position, 1);
	return Memory[position] = value;
}


template<typename T>
void SimpleList<T>::moveMemoryTo(T* memory, int length)
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
void SimpleList<T>::memMove(T* dst, const T* src, int length)
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

template <typename T, typename C, C T::*Member>
int SimpleMap<T,C,Member>::findIndex(const C& index)
{
	int min = 0;
	int max = Data.UsedLength-1;
	int mid = max / 2;
	while(min <= max)
	{
		if(index < Data[mid].*Member)
			max = mid - 1;
		else if(index > Data[mid].*Member)
			min = mid + 1;
		else
			break;
		mid = min + ((max-min) / 2);
	}
	return mid;
};

template <typename T, typename C, C T::*Member>
T& SimpleMap<T,C,Member>::operator[](const C& index)
{
	int i = findIndex(index);
	if(i < Data.UsedLength)
		if(Data[i].*Member == index)
			return Data[i];
	
	T t{};
	t.*Member = index;
	return Data.insert(i, t);
}

template <typename T, typename C, C T::*Member>
T& SimpleMap<T,C,Member>::insert(const T& t)
{
	int i = findIndex(t.*Member);
	return Data.insert(i, t);
}

template <typename T, typename C, C T::*Member>
void SimpleMap<T,C,Member>::sort()
{
	for (int i = 1; i < Data.UsedLength; ++i)
	{
		T& temp = Data[i];
		int j = i -1;
		
		while(j >= 0 && Data[j].*Member > temp.*Member)
		{
			Data[j + 1] = Data[j];
			j--;
		}
		
		Data[j+1] = temp;
	}
}