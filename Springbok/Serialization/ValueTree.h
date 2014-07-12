//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <vector>
#include <string>

class ValueTree
{
public:
	template<class A, class B>
	using Map     = std::vector<std::pair<A, B>>;
	using StrList = std::vector<std::string>;
public:
	ValueTree(){};
	ValueTree(const std::string& name);
	
	StrList& attr(const std::string& name);
	
	std::string getValue(const std::string& spec) const;
	StrList      getList(const std::string& spec) const;
	const ValueTree* getSubTree(const std::string& spec) const;
	
	std::string& insertValue(const std::string& spec);
	StrList&     insertList(const std::string& spec);
	ValueTree*   insertSubTree(const std::string& spec);
	
	// The actual functions, the above are just shortcuts
	void findPathSpec(const std::string& spec, bool* found, const StrList** retValue, const ValueTree** retSubtree, const ValueTree** lastFoundParent = nullptr, std::string* relativeToLast = nullptr) const;
public:
	Map<std::string, StrList> Values;
	std::vector<ValueTree>      Children;
	std::string               Identifier = "_root_";
};