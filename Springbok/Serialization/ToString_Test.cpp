//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "ToString_Types.h"
#include <SSTest.h>

namespace
{
	void _ToString()
	{
		SST_M_ASSERT_START;
		SST_M_ASSERT_EQ(ToString(4), "4");
		SST_M_ASSERT_EQ(ToString(2.2), "2.2");
		SST_M_ASSERT_EQ(ToString(Vec2F(0)), "(0, 0)");
		SST_M_ASSERT_EQ(ToString(Vec3F(1)), "(1, 1, 1)");
		SST_M_ASSERT_EQ(ToString(Vec4I(2)), "(2, 2, 2, 2)");
		SST_M_ASSERT_END;
	}
	
	SST::SimpleTest __ToString("Serialization/ToString", &_ToString, SST::Required);
	
}