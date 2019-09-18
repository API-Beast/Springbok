#include "Vec2.h"
#include "Vec2_Extra.h"
#include <SSTest.h>

namespace
{
	void _Vec2()
	{
		SST_M_ASSERT_START;
		SST_M_ASSERT_EQ(Vec2F(0.25, 0) + Vec2F(0.25, 0), Vec2F(0.5, 0.0));
		SST_M_ASSERT_EQf(Vec2F(2.0f, 0.25f).normalized().length(), 1.f);
		SST_M_ASSERT(Vec2F(0, 0) < Vec2F(0, 1));
		SST_M_ASSERT(Vec2F(0, 0) < Vec2F(1, 0));
		SST_M_ASSERT(Vec2F(0, 0) < Vec2F(1, 1));
		SST_M_ASSERT(Vec2F(0, 1) < Vec2F(1, 1));
		SST_M_ASSERT(Vec2F(1, 0) < Vec2F(1, 1));
		SST_M_ASSERT_END;
	}
	
	SST::SimpleTest __Vec2("Vec2", &_Vec2, SST::Required);
	
}