//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "CliArgumentParser.h"
#include <SSTest.h>

namespace
{
	void _CliArgumentParser()
	{
		CliArgumentParser parser;
		parser.addSwitch("--fullscreen", "-f");
		parser.addSwitch("--size", 2);
		parser.addSwitch("--debug", "-d");
		
		char* testData[] = {"-f", "--size", "128", "128"};
		parser.parse(4, testData);
		
		SST_M_ASSERT_START;
		SST_M_ASSERT_EQ(parser["--fullscreen"].IsSet, true);
		SST_M_ASSERT_EQ(parser["--size"].IsSet, true);
		SST_M_ASSERT_EQ(parser["--size"].Parameters[0], "128");
		SST_M_ASSERT_EQ(parser["--size"].Parameters[1], "128");
		SST_M_ASSERT_EQ(parser["--debug"].IsSet, false);
		SST_M_ASSERT_END;
	}
	
	SST::SimpleTest __CliArgumentParser("CliArgumentParser", &_CliArgumentParser, SST::Required);
	
}