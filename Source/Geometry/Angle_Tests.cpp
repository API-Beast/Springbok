#include "Angle.h"
#include <SSTest.h>

namespace
{
	void _Angle()
	{
		SST_M_ASSERT_START;
		
		SST_M_ASSERT_EQf(0.7_turn += 0.2_turn, 0.9_turn);
		SST_M_ASSERT_EQf(0.9_turn += 0.2_turn, 0.1_turn);
		
		SST_M_ASSERT_EQf(0.3_turn -= 0.2_turn, 0.1_turn);
		SST_M_ASSERT_EQf(0.1_turn -= 0.2_turn, 0.9_turn);
		
		SST_M_ASSERT_EQf(0.7_turn +  0.2_turn, -0.1_turn);
		SST_M_ASSERT_EQf(0.9_turn +  0.2_turn,  0.1_turn);
		
		SST_M_ASSERT_EQf(0.3_turn -  0.2_turn,  0.1_turn);
		SST_M_ASSERT_EQf(0.1_turn -  0.2_turn, -0.1_turn);
		SST_M_ASSERT_EQf(0.9_turn -  0.7_turn,  0.2_turn);
		
		SST_M_ASSERT_EQf(Angle(-0.1f).Data, -0.1f);
		SST_M_ASSERT_EQf((-0.1_turn).Data, -0.1f);
		
		SST_M_ASSERT_EQf(-(0.6_turn), 0.4_turn);
		SST_M_ASSERT_EQf(-(0.3_turn), 0.7_turn);
		
		SST_M_ASSERT_EQf(0.5_turn + 4.62_turn , 0.12_turn);
		
		SST_M_ASSERT_EQ((0.00_turn).toDirection(), Vec2F( 0.0f, -1.f));
		SST_M_ASSERT_EQ((0.50_turn).toDirection(), Vec2F( 0.0f,  1.f));
		SST_M_ASSERT_EQ((0.25_turn).toDirection(), Vec2F( 1.0f,  0.0f));
		SST_M_ASSERT_EQ((0.75_turn).toDirection(), Vec2F(-1.0f,  0.0f));
		
		SST_M_ASSERT_END;
	}
	
	SST::SimpleTest __Angle("Angle", &_Angle, SST::Required);
	
}