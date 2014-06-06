// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#include "ObjectPointer.h"

#include <cassert>

void DestructorBase::destroy(void* pointer)
{
	assert(pointer == nullptr);
}

void Destructor<void>::destroy(void* pointer)
{
	assert(pointer == nullptr);
};

ObjectData::~ObjectData()
{
	delete Destructor;
}

std::list< ObjectData >& ObjectData::ObjectDataList()
{
	// Bug #14 - ObjectData was destroyed before ResourceManager
	// Destruction order is dependend from Construction Order
	// So we need to lazy-initialize this
	static std::list<ObjectData> objects;
	return objects;
}