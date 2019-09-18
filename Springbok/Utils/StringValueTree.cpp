//  Copyright (C) 2015 Manuel Riecke <api.beast@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "StringValueTree.h"

StringValueTree::StringValueTree()
{
	this->Root = this;
}

StringValueNode::StringValueNode(StringValueNode* parent)
{
	this->Root = parent->Root;
	parent->appendNode(this);
}

void StringValueNode::appendNode(StringValueNode* node)
{
	StringValueNode* child = this->Children;
	
	if(child)
	while(child->NextSibling) child=child->NextSibling;
	
	if(!child)
		this->Children = node;
	else
		child->NextSibling = node;
}

StringValueNode* StringValueNode::appendNode()
{
	return this->Root->allocNode(this);
}

void StringValueTree::free(const char* string)
{
	if(string != nullptr)
	if(Pool.isInPool(string))
		Pool.freeCString(string);
}

const char* StringValueTree::allocString(const char* string)
{
	return Pool.allocateCString(string);
}

const char* StringValueTree::allocString(const char* start, int length)
{
	return Pool.allocateSubstring(start, length);
}

StringValueNode* StringValueTree::allocNode(StringValueNode* parent)
{
	return Pool.create<StringValueNode>(parent);
}

void StringValueNode::setKey(const char* string)
{
	Root->free(Key);
	Key = nullptr;
	Key = Root->allocString(string);
}

void StringValueNode::setValue(const char* string)
{
	Root->free(Value);
	Value = nullptr;
	Value = Root->allocString(string);
}

void StringValueNode::setType(const char* type)
{
	Root->free(Type);
	Type  = nullptr;
	Type  = Root->allocString(type);
}

void StringValueNode::setKey(const char* start, int length)
{
	Root->free(Key);
	Key = nullptr;
	Key = Root->allocString(start, length);
}

void StringValueNode::setType(const char* start, int length)
{
	Root->free(Type);
	Type = nullptr;
	Type = Root->allocString(start, length);
}

void StringValueNode::setValue(const char* start, int length)
{
	Root->free(Value);
	Value = nullptr;
	Value = Root->allocString(start, length);
}


StringValueNode* StringValueNode::insertValue(const char* key, const char* value, const char* type)
{
	StringValueNode* node = Root->allocNode(this);
	
	node->Key   = Root->allocString(key);
	node->Value = Root->allocString(value);
	node->Type  = Root->allocString(type);
	
	return node;
}

StringValueNode* StringValueNode::appendArrayElement(const char* string, const char* type)
{
	StringValueNode* node = Root->allocNode(this);
	
	node->Value = Root->allocString(string);
	node->Type  = Root->allocString(type);
	
	Root->free(this->Type);
	//this->Type = Root->alloc("array");
	this->Type = "array";
	
	return node;
}

