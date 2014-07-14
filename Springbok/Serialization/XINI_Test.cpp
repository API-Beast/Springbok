//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "XINI.h"
#include <Springbok/Platform/FileSystem.h>
#include <SSTest.h>

namespace
{
	void _XINI()
	{
		std::string filePath   = FileSystem::ParentPath(__FILE__)+"/TestFiles/";
		ValueTree simpleXINI = LoadXINI(filePath+"Basic.xini");
		SST_M_ASSERT_START;
		SST_M_ASSERT_EQ(simpleXINI.value("Group.Key"), "Value");
		SST_M_ASSERT_EQ(simpleXINI.value("Group.String"), "ABCDEF");
		auto array = simpleXINI.array("Group.Array");
		if(array.size() == 3)
		{
			SST_M_ASSERT_EQ(array[0], "A");
			SST_M_ASSERT_EQ(array[1], "B");
			SST_M_ASSERT_EQ(array[2], "C");
		}
		else
			SST_M_ASSERT_EQ(array.size(), 3);
		auto largeGroup = simpleXINI.subTree("LargeGroup");
		if(largeGroup)
		{
			SST_M_ASSERT_EQ(largeGroup->Children.size(), 2);
			SST_M_ASSERT_EQ(largeGroup->Children[0].value("SubValue"), "10");
			SST_M_ASSERT_EQ(largeGroup->Children[1].value("SubValue"), "20");
		}
		else
			SST_M_ASSERT(largeGroup);
		SST_M_ASSERT_END;
	}
	
	void _multiline()
	{	
		std::string filePath   = FileSystem::ParentPath(__FILE__)+"/TestFiles/";
		ValueTree multiline  = LoadXINI(filePath+"Multiline.xini");
		SST_M_ASSERT_START;
		SST_M_ASSERT_EQ(multiline.value("Description"), "A value can\nspan multiple\nlines");
		
		auto array = multiline.array("Group.MultiLineArray");
		if(array.size() == 4)
		{
			SST_M_ASSERT_EQ(array[0], "A Array");
			SST_M_ASSERT_EQ(array[1], "should be able");
			SST_M_ASSERT_EQ(array[2], "to span multiple lines");
			SST_M_ASSERT_EQ(array[3], "too");
		}
		else
			SST_M_ASSERT_EQ(array.size(), 4);
		
		SST_M_ASSERT_END;
	}
	
	SST::SimpleTest __XINI("Serialization/XINI", &_XINI, SST::Required);
	SST::SimpleTest _XINI_multiline("Serialization/XINI::multiline", &_multiline, SST::Required);
}