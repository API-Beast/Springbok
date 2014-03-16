#pragma once

template<typename T, int MaxElements>
/** A RingBuffer is a lightweight container with a maximum length, if this limit is reached old elements will be overwritten.
 *  This allows allocating the RingBuffer on the stack and makes it suitable as quasi-dynamic container for performance intensive code
 *  such as Physics or Rendering code.
 *  This class is optimized for speed and for high level use other container classes are preferable.
 *  @tparam T The type of the data that will be saved in this Ringbuffer.
 *  @tparam MaxElements The amount of memory that will be allocated on the stack. */
class RingBuffer
{
public:
	T&  back(){ return *End;   };
	T& front(){ return *Start; };
	
	void pushBack(const T& value);
	void pushFront(const T& value);
	
	// "const T&" instead of "T" because the memory is never freed, it gives some very minor speed boost for things like foo(buffer.popBack())
	const T& popBack();
	const T& popFront();
private:
	// Not "T Elements[MaxElements];" so the values aren't initialized on memory aquisation.
	char Memory[MaxElements * sizeof(T)];
	T* Start = (T*)Memory;
	T* End = (T*)Memory;
private:
	void moveBackward(T*& ptr);
	void moveForward(T*& ptr);
};

template<typename T, int MaxElements>
void RingBuffer<T, MaxElements>::moveBackward(T*& ptr)
{
	ptr--;
	// Ughhh... liness.
	if(ptr <= (T*)(&(Memory[0])))
		ptr = (T*)(&(Memory[MaxElements * sizeof(T)]));
};

template<typename T, int MaxElements>
void RingBuffer<T, MaxElements>::moveForward(T*& ptr)
{
	ptr++;
	if(ptr >= (T*)(&(Memory[MaxElements * sizeof(T)])))
		ptr = (T*)(&(Memory[0]));
};

template<typename T, int MaxElements>
void RingBuffer<T, MaxElements>::pushBack(const T& value)
{
	moveForward(End);
	(*End) = value;
	
	if(End == Start)
		moveForward(Start);
};

template<typename T, int MaxElements>
void RingBuffer<T, MaxElements>::pushFront(const T& value)
{
	moveBackward(Start);
	(*Start) = value;
	
	if(End == Start)
		moveBackward(End);
};