//  Copyright (C) 2015 Manuel Riecke <api.beast@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "MemoryPool.h"

struct StringValueTree;

//~ ### StringValueTree
//~ *Dependencies: MemoryPool.h*
//~
//~ StringValueTree is a intermediate representation of the data stored in a configuration file.
//~ Formats such as XML, JSON and INI can all be accurately stored in this data structure.
//~ As such all three can be imported and exported to this format without losing any crucial data.
//~ Comments and intendation are not stored.
//~ 
//~ #### Nodes (struct StringValueNode)
struct StringValueNode
{
	//~
	StringValueNode() = default;
	StringValueNode(StringValueNode* parent);
	
	const char* Key   = nullptr;
	const char* Value = nullptr;
	const char* Type  = nullptr; // Meta-Data: "string" = value is a string, "number" = value is a number, "array" = children are inline-array, etc.
	
	StringValueNode* Children    = nullptr;
	StringValueNode* NextSibling = nullptr; // Single linked list for traversal.
	
	StringValueTree* Root = nullptr; // Used for memory allocations.
	
	void appendNode(StringValueNode* node);
	StringValueNode* appendNode();
	
	void setKey  (const char* string);
	void setValue(const char* string);
	void setType (const char* type);
	
	void setKey  (const char* start, int length);
	void setValue(const char* start, int length);
	void setType (const char* start, int length);
	
	StringValueNode* appendArrayElement(const char* string, const char* type="string"); // Will set *this->Type* to "array"
	StringValueNode* insertValue(const char* key, const char* value, const char* type="string");
};
//~ #### Root (struct StringValueTree)
//~ The Root itself inherits all properties of a Node, but in additions keeps track of all memory allocations.
struct StringValueTree : public StringValueNode
{
	//~
	StringValueTree();
	StringValueTree(const StringValueTree& other) = delete; // Don't pass StringValueTree by value, too big, too many pointers.
	// Implicit destructor, will destroy the MemoryPool and thus makes all the allocated strings invalid.
	
	void free(const char* string);
	const char* allocString(const char* string);
	const char* allocString(const char* start, int length);
	StringValueNode* allocNode(StringValueNode* parent);
	
	MemoryPool Pool;
};