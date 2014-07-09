//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "CliArgumentParser.h"

CliArgumentParser::SwitchDefinition* CliArgumentParser::find(CliArgumentParser::string name)
{
	for(auto& def : Switches)
		for(std::string& str : def.Names)
			if(str == name)
				return &def;
	return nullptr;
}

CliArgumentParser::SwitchDefinition& CliArgumentParser::operator[](CliArgumentParser::string name)
{
	auto* def = find(name);
	if(def)
		return *def;
			
	SwitchDefinition definition;
	definition.Names.push_back(name);
	Switches.push_back(definition);
	return Switches.back();
}

void CliArgumentParser::addSwitch(CliArgumentParser::string name, CliArgumentParser::string alias, int parameter, bool optionalParameters)
{
	addSwitch(name, parameter, optionalParameters);
	addAlias(name, alias);
}

void CliArgumentParser::addSwitch(CliArgumentParser::string name, int parameter, bool optionalParameters)
{
	SwitchDefinition definition;
	definition.Names.push_back(name);
	definition.AcceptedParameters = parameter;
	definition.ParametersOptional = optionalParameters;
	
	Switches.push_back(definition);
}

void CliArgumentParser::addAlias(CliArgumentParser::string name, CliArgumentParser::string alias, CliArgumentParser::string alias2)
{
	addAlias(name, alias);
	addAlias(name, alias2);
}

void CliArgumentParser::addAlias(CliArgumentParser::string name, CliArgumentParser::string alias)
{
	(*this)[name].Names.push_back(alias);
}

std::string CliArgumentParser::getSyntax()
{
	std::string retVal;
	for(SwitchDefinition& def : Switches)
	{
		retVal += "["+def.Names[0]+" ";
		bool first = true;
		for(std::string name : def.Names)
		{
			if(!first)
				retVal += " | " + name;
			first = false;
		}
		if(def.AcceptedParameters)
		{
			if(def.ParametersOptional)
				retVal+="[";
			if(def.AcceptedParameters < 4)
				for(int i = 0; i < def.AcceptedParameters; ++i)
				{
					if(i) retVal+=" ";
					retVal+="arg"+std::to_string(i);
				}
			else
				retVal+="args...";
			if(def.ParametersOptional)
				retVal+="]";
		}
		retVal+="]";
	}
	return retVal;
}

void CliArgumentParser::parse(int argc, char** argv)
{
	std::vector<std::string> converted;
	for(int i = 0; i < argc; ++i)
		converted.push_back(argv[i]);
	parse(converted);
}

void CliArgumentParser::parse(const std::vector< std::string >& arguments)
{
	std::string curKey;
	SwitchDefinition* curSwitch = nullptr;
	int i = 0;
	bool endParsing = false;
	for(std::string curArgument : arguments)
	{
		if(curArgument == "--")
		{
			endParsing = true;
			continue;
		}
		
		if(endParsing)
		{
			LooseArguments.push_back(curArgument);
			continue;
		}
		
		auto eqPos = curArgument.find('=');
		if(eqPos != std::string::npos)
		{
			curKey = curArgument.substr(0, eqPos);
			curSwitch = find(curKey);
			if(curSwitch)
			{
				curSwitch->IsSet = true;
				curSwitch->Parameters.push_back(curArgument.substr(eqPos));
				continue;
			}
		}
		else
		{
			auto* temp = find(curArgument);
			if(temp)
			{
				curSwitch = temp;
				curSwitch->IsSet = true;
				continue;
			}
		}
		
		if(curSwitch && curSwitch->Parameters.size() < curSwitch->AcceptedParameters)
			curSwitch->Parameters.push_back(curArgument);
		else
			LooseArguments.push_back(curArgument);
	}
}