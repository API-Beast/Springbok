// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once
#include <list>

//! @cond
struct DestructorBase
{
	virtual void destroy(void* pointer);
};

template<typename T>
struct Destructor : public DestructorBase
{
	virtual void destroy(void* pointer);
};

template<>
struct Destructor<void> : public DestructorBase
{
	virtual void destroy(void* pointer);
};

struct ObjectData
{
	void* MemoryLocation = nullptr;
	DestructorBase* Destructor = nullptr;
public:
	ObjectData() = default;
	template<typename T>
	ObjectData(T* ptr) : MemoryLocation(ptr){};
	~ObjectData();
	bool operator<(const ObjectData& other) const { return MemoryLocation < other.MemoryLocation; };
	bool operator==(const ObjectData& other) const {  return MemoryLocation && (MemoryLocation == other.MemoryLocation); };
	static std::list<ObjectData> gObjects;
};

//! @endcond

//! @ingroup ObjectPointer
template<class T>
class ObjectPointer
{
public:
	ObjectPointer();
	template<class U>
	ObjectPointer(U* ptr);
	ObjectPointer(std::nullptr_t null);
	ObjectPointer(const ObjectPointer< T >& other);
	ObjectPointer<T>& operator =(const ObjectPointer< T >& other);
	T* operator->() const;
	operator T*() const;
	void replaceWith(T* newPtr);
	void destroy();
protected:
	void markAsDestroyed(T* memory);
private:
	ObjectData* mPointer;
};

/** @name pointer_cast
 *  Converts to \a ptr to raw pointer which is then cast to a pointer of type \a X.
 *  @returns The cast pointer.
 *  @relates ObjectPointer */
//@{
template<typename X, template<typename> class T, typename Y>
X dynamic_pointer_cast(const T<Y>& ptr);
template<typename X, template<typename> class T, typename Y>
X reinterpret_pointer_cast(const T<Y>& ptr);
template<typename X, template<typename> class T, typename Y>
X static_pointer_cast(const T<Y>& ptr);
//@}

#include "ObjectPointer_Templates.hpp"