//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "ValueTree.h"
#include <Springbok/Parsing.hpp>
#include <algorithm>

using namespace std;

ValueTree::ValueTree(const string& name)
{
	Identifier = name;
}

ValueTree::StrList& ValueTree::attr(const string& name)
{
	auto value = find_if(Values.begin(), Values.end(),
							 [name](const pair<string, StrList>& x){ return x.first == name; });
	if(value != Values.end())
	{
		return value->second;
	}
	else
	{
		Values.push_back(make_pair(name, StrList()));
		return Values.back().second;
	}
}

ValueTree::StrList ValueTree::array(const string& spec) const
{
	const StrList* list = nullptr;
	findPathSpec(spec, nullptr, &list, nullptr);
	if(list)
		return *list;
	else
		return StrList();
}

const ValueTree* ValueTree::subTree(const string& spec) const
{
	const ValueTree* tree = nullptr;
	findPathSpec(spec, nullptr, nullptr, &tree);
	return tree;
}

string ValueTree::value(const string& spec) const
{
	const StrList* list = nullptr;
	findPathSpec(spec, nullptr, &list, nullptr);
	if(list)
		return (*list)[0];
	else
		return "";
}

ValueTree::StrList& ValueTree::insertArray(const string& spec)
{
	size_t dotPos = spec.find_last_of('.');
	ValueTree* tree = this;
	string key = spec;
	if(dotPos != string::npos)
	{
		tree = insertSubTree(spec.substr(0, dotPos));
		key  = spec.substr(dotPos+1);
	}
	return tree->attr(key);
}

string& ValueTree::insertValue(const string& spec)
{
	size_t dotPos = spec.find_last_of('.');
	ValueTree* tree = this;
	string key = spec;
	if(dotPos != string::npos)
	{
		tree = insertSubTree(spec.substr(0, dotPos));
		key  = spec.substr(dotPos+1);
	}
	StrList& list = tree->attr(key);
	if(!list.size())
		list.push_back("");
	return list[0];
}

ValueTree* ValueTree::insertSubTree(const string& spec)
{
	StringParser p(spec);
	ValueTree* context = this;
	while(!p.atEnd())
	{
		string subspec = p.advanceTo(Codepoint('.'));
		// Does it already exist?
		auto child = find_if(context->Children.begin(), context->Children.end(),
															[subspec](const ValueTree& x){ return x.Identifier == subspec; });
		if(child == context->Children.end())
		{
			context->Children.push_back(subspec);
			context = &(context->Children.back());
		}
		else
			context = &(*child);
	}
	return context;
}

void ValueTree::findPathSpec(const string& spec, bool* found, const StrList** retValue, const ValueTree** retSubtree, const ValueTree** lastFoundParent, string* relativeToLast) const
{
	StringParser p(spec);
	const ValueTree* context = this;
	while(!p.atEnd())
	{
		string subspec = p.advanceTo(Codepoint('.'));
		// Is it a value?
		if(p.atEnd()) // Only the last subspec can refer to a value
		{
			auto value = find_if(context->Values.begin(), context->Values.end(),
			             [subspec](const pair<string, StrList>& x){ return x.first == subspec; });
			if(value != context->Values.end())
			{
				if(found)    *found    = true;
				if(retValue) *retValue = &(value->second);
				return;
			}
			else; // Fall through, check for child instead
		}
		// Is it a child?
		auto child = find_if(context->Children.begin(), context->Children.end(),
															[subspec](const ValueTree& x){ return x.Identifier == subspec; });
		if(child != context->Children.end())
		{
			context = &(*child);
		
			if(p.atEnd())
			{
				if(found)      *found      = true;
				if(retSubtree) *retSubtree = &(*context);
				return;
			}
			continue;
		}
		// It is neither. Fail.
		if(found) *found = false;
		if(lastFoundParent) *lastFoundParent = &(*context);
		if(relativeToLast)  *relativeToLast  = p.advanceTo(Codepoint('\0'));
		return;
	}
	if(found) *found = false;
	return;
}