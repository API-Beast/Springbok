#include <SSTest.h>
#include "Operations.h"
namespace
{
bool tests()
{
	SST_M_ASSERT_START;
	
	// Power
	SST_M_ASSERT_EQ(Power<1>(2), 2);
	SST_M_ASSERT_EQ(Power<2>(2), 4);
	SST_M_ASSERT_EQ(Power<3>(2), 8);
	SST_M_ASSERT_EQ(Power<4>(2),16);
	
	SST_M_ASSERT_EQ(Root<1>( 2), 2);
	SST_M_ASSERT_EQ(Root<2>( 4), 2);
	SST_M_ASSERT_EQ(Root<3>( 8), 2);
	SST_M_ASSERT_EQ(Root<4>(16), 2);
	
	
	// Square Root
	SST_M_ASSERT_EQf(Root<2>(432.324f), SquareRoot(432.324f));
	auto testRoot = Root(27.f, 3);
	auto testPower= Power(testRoot, 3);
	SST_M_ASSERT_EQf(testPower, 27.f);
	
	
	// Round
	SST_M_ASSERT_EQf(Round(3.215f), 3);
	SST_M_ASSERT_EQf(Round(3.215f, 0.1f), 3.2f);
	
	SST_M_ASSERT_EQf(Round(4.f), 4);
	SST_M_ASSERT_EQf(Round(4.f, 0.1f), 4.f);
	
	auto testRound = Round(4.31, 0.2);
	float testRoundA = Round(testRound, 0.1f);
	SST_M_ASSERT_EQf(testRound, 4.4);
	SST_M_ASSERT_EQf(testRoundA, 4.4f);
	
	
	// Modulo
	SST_M_ASSERT_EQf(Modulo( 1.5f, 1.f), fmod( 1.5f, 1.f));
	SST_M_ASSERT_EQf(Modulo( 1.9f, 1.f), fmod( 1.9f, 1.f));
	
	SST_M_ASSERT_EQf(PositiveModulo(-0.1f, 1.f), 0.9f);
	SST_M_ASSERT_EQf(PositiveModulo(-0.4f, 1.f), 0.6f);
	SST_M_ASSERT_EQf(PositiveModulo(-1.6f, 1.f), 0.4f);
 
	SST_M_ASSERT_END;
	
	
	return true;
}

SST::SimpleTest a("Math/Operations", &tests, SST::Required);
}