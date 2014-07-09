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
	template<class T>
	using std::vector    = std::vector<T>;
	template<class A, class B>
	using Map     = std::vector<std::pair<A, B>>;
	using String  = std::string;
	using StringC = const std::string&;
	using StrList = std::vector<std::string>;
public:
	ValueTree(){};
	ValueTree(StringC name);
	
	StrList& attr(StringC name);
	
	String     getValue  (StringC spec) const;
	StrList    getList   (StringC spec) const;
	const ValueTree* getSubTree(StringC spec) const;
	
	String&    insertValue  (StringC spec);
	StrList&   insertList   (StringC spec);
	ValueTree* insertSubTree(StringC spec);
	
	// The actual functions, the above are just shortcuts
	void findPathSpec(StringC spec, bool* found, const StrList** retValue, const ValueTree** retSubtree, const ValueTree** lastFoundParent = nullptr, String* relativeToLast = nullptr) const;
public:
	Map<String, StrList> Values;
	std::vector<ValueTree>      Children;
	String               Identifier = "_root_";
};