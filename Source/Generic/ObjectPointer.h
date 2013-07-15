// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once
#include <list>

//! @cond
class AbstractObjectPointer
{
public:
	virtual void onDestruction(void* ptr){};
	virtual void onReplace(void* oldPtr, void* newPtr){};
	static std::list<AbstractObjectPointer*> gInstances;
};
//! @endcond

//! @ingroup ObjectPointer
template<class T>
class ObjectPointer : public AbstractObjectPointer
{
public:
	ObjectPointer();
	ObjectPointer(T* ptr);
	ObjectPointer(const ObjectPointer< T >& other);
	~ObjectPointer();
	ObjectPointer<T>& operator =(T* ptr);
	ObjectPointer<T>& operator =(const ObjectPointer< T >& other);
	operator T*() const;
	void replaceWith(T* newPtr, bool del=true);
	void destroy(bool del=true);
	virtual void onDestruction(void* ptr);
	virtual void onReplace(void* oldPtr, void* newPtr);
protected:
	void markAsDestroyed(T* memory);
private:
	T* mPointer;
	std::list<AbstractObjectPointer*>::iterator mIter;
};

/** @name pointer_cast
 *  Converts to \a ptr to raw pointer which is then cast to a pointer of type \a X.
 *  @returns The cast pointer.
 *  @relates ObjectPointer */
//@{
template<typename X, template<typename> class T, typename Y>
X* dynamic_pointer_cast(const T<Y>& ptr);
template<typename X, template<typename> class T, typename Y>
X* reinterpret_pointer_cast(const T<Y>& ptr);
template<typename X, template<typename> class T, typename Y>
X* static_pointer_cast(const T<Y>& ptr);
//@}

#include "ObjectPointer_Templates.hpp"