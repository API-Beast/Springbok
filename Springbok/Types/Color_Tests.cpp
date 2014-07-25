//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "Color.h"
#include <SSTest.h>
#include <iostream>

namespace
{
	void _Color()
	{
		SST_M_ASSERT_START;
		Vec3F a = 0.5;
		Vec3F b = Lab2RGB(RGB2Lab(a));
		SST_M_ASSERT(Distance(0.5, b) < 0.001f);
		a = 0.0954;
		b = Lab2RGB(RGB2Lab(a));
		SST_M_ASSERT(Distance(0.0954, b) < 0.001f);
		SST_M_ASSERT_END;
	}
	
	SST::SimpleTest __Color("Types/Color", &_Color, SST::Required);
	
}