#include <SSTest.h>
#include "Operations.h"
namespace
{
bool tests()
{
	SST_M_ASSERT_START;
	SST_M_ASSERT(Power<1>(2) ==  2);
	SST_M_ASSERT(Power<2>(2) ==  4);
	SST_M_ASSERT(Power<3>(2) ==  8);
	SST_M_ASSERT(Power<4>(2) == 16);
	
	SST_M_ASSERT(Root<1>( 2) == 2);
	SST_M_ASSERT(Root<2>( 4) == 2);
	SST_M_ASSERT(Root<3>( 8) == 2);
	SST_M_ASSERT(Root<4>(16) == 2);
	
	SST_M_ASSERT(Root<2>(432.324f) == SquareRoot(432.324f));
	auto testRoot = Root(27.f, 3);
	auto testPower= Power(testRoot, 3);
	SST_M_ASSERT(testPower == 27.f);
	SST_M_ASSERT_END;
	return true;
}

SST::SimpleTest a("Math/Operations", &tests, SST::Required);
}