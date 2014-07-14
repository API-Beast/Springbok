//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "XINI.h"
#include <Springbok/Parsing.hpp>
#include <Springbok/Utils.hpp>
#include <Springbok/Generic/Logic.h>
#include <vector>

using namespace std;

namespace
{
	vector<string> ParseArray(StringParser p)
	{
		p.next(); // Skip the first '['
		vector<string> result;
		while(!p.atEnd())
		{
			auto curItem = p.advanceTo(U',');
			if(p.atEnd())
				if(curItem.back() == ']')
					curItem = UTF8::Chop(curItem, 0, 1);
			
			if(curItem[0] == '"' && curItem.back() == '"')
				curItem = UTF8::Chop(curItem, 1, 1);
			
			result.push_back(curItem);
		};
		return result;
	};
};

void LoadXINI(const std::string& content, ValueTree* parent)
{
	StringParser p(content);
	ValueTree* context = parent;
	p.StripWhitespace = true;
	p.SkipWhitespace  = true;
	
	auto isOperator = InSet({'=', '{', '[', ';', '#'});
	
	std::string key, value;
	bool unfinalizedEntry = false;
	while(!p.atEnd())
	{
		key = p.advanceTo(isOperator);
		Codepoint oper = p.last();
		bool enclosed = false;
		switch(oper)
		{
			// ------------------------------------------------------------------
			// ### [ShallowChild]
			// ------------------------------------------------------------------
			case '[':
				parent->Children.emplace_back(p.advanceTo(U']'));
				context = &(parent->Children.back());
				break;
			// ------------------------------------------------------------------
			// ### DeepChild{ [...] }
			// ------------------------------------------------------------------
			case '{':
				parent->Children.emplace_back(key);
				LoadXINI(p.advanceToNested(U'{', U'}'), &(parent->Children.back()));
				break;
			// ------------------------------------------------------------------
			// ### # A Comment
			// ------------------------------------------------------------------
			case ';': // For INI compatiblity
			case '#':
				p.advanceTo(U'\n');
				break;
			// ------------------------------------------------------------------
			// ### Key = Value
			// ------------------------------------------------------------------
			case '=':
				value = p.advanceTo(U'\n');
				if(value.back() == '"')
				{
					value = UTF8::Chop(value, 1, 1);
					enclosed = true;
				}
				while(true)
				{
					StringParser lookAhead = p;
					// Look at the next line, if it is not a valid [ABC], ABC{} or A=B structure consume it.
					std::string newKey = lookAhead.advanceTo(Or(isOperator, InSet({',', '"', '\n'})));
					bool properSyntax = isOperator(lookAhead.last()) && newKey.find_first_of(' ') == -1;
					
					std::string add = "";
					if(!properSyntax)
						add = p.advanceTo(U'\n');
					
					if(add.empty() || properSyntax)
					{
						if(!enclosed && value.front() == '[' && value.back() == ']')
							context->insertArray(key) = ParseArray(value);
						else
							context->insertValue(key) = value;
						break;
					}
					else
					{
						if(add.front()=='"' && add.back()=='"')
							add = UTF8::Chop(add, 1, 1);
						value += "\n";
						value += add;
					}
				}
				break;
			default:
				Debug::Write("XINI parser is broken. Unimplemented operator: $", oper);
		}
		
	}
}

ValueTree LoadXINI(const std::string& path)
{
	ValueTree root;
	LoadXINI(ReadFileFull(path), &root);
	return root;
}

void WriteXINI(const ValueTree& tree, std::ostream& out, int intendation)
{
	std::string intend  = std::string(intendation * 2, ' ');
	bool anyContent = false;
	auto printEntry = [&out](const std::string& entry)
	{
		if(entry.empty())
			out << "\"\"";
		else if(entry.size() > 10
			   || entry != UTF8::Strip(entry, &UCS::IsWhitespace)
				 || entry != UTF8::Strip(entry, U'"'))
			out << '"' << entry << '"';
		else
			out << "" << entry;
	};
	
	for(auto value : tree.Values)
	{
		const string&  key = value.first;
		const vector<string>& val = value.second;
		out << intend << key << "=";
		if(val.size() == 1)
		{
			printEntry(val[0]);
			out << std::endl;
		}
		else
		{
			bool first = true;
			out << '[';
			for(string entry : val)
			{
				if(!first)
					out << ", ";
				printEntry(entry);
				first = false;
			}
			out << ']' << std::endl;
		}
		anyContent = true;
	}
	
	for(const ValueTree& child : tree.Children)
	{
		bool isComplex = !child.Children.empty();
		bool miniObj = !isComplex & child.Values.size() == 1;
		if(anyContent)
		{
			out << '\n';
			anyContent = child.Values.size() > 1;
		}
		
		if(isComplex)
		{
			out << intend << child.Identifier << '\n';
			out << intend << '{' << std::endl;
		}
		else if(miniObj)
			out << intend << '[' << child.Identifier  << ']';
		else
			out << intend << '[' << child.Identifier  << ']' << std::endl;
		
		WriteXINI(child, out, intendation+isComplex);
		
		if(isComplex)
			out << intend << '}' << std::endl;
	}
}