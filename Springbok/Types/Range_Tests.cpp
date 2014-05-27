#include "Range.h"
#include <SSTest.h>

namespace
{
	
void basicUsage()
{
	//! [intersect]
	RangeF a(-0.4f, 0.7f);
	RangeF result = a.intersect(0.0f, 1.0f);
	// Result == (0.0f, 0.7f)
	//! [intersect]
	SST_M_ASSERT_START;
	SST_M_ASSERT(result.MinVal == 0.0f);
	SST_M_ASSERT(result.MaxVal == 0.7f);
	SST_M_ASSERT_END;
}

	
SST::SimpleTest a("Math/Range", &basicUsage,  SST::Required);
}