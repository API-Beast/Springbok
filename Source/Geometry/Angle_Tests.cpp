#include "Angle.h"
#include <SSTest.h>

namespace
{
	void _Angle()
	{
		SST_M_ASSERT_START;
		
		SST_M_ASSERT_EQf(Angle(0.7f) += 0.2f, 0.9f);
		SST_M_ASSERT_EQf(Angle(0.9f) += 0.2f, 0.1f);
		
		SST_M_ASSERT_EQf(Angle(0.3f) -= 0.2f, 0.1f);
		SST_M_ASSERT_EQf(Angle(0.1f) -= 0.2f, 0.9f);
		
		SST_M_ASSERT_EQf((Angle(0.7f) +  0.2f).angle, 0.9f);
		SST_M_ASSERT_EQf((Angle(0.9f) +  0.2f).angle, 0.1f);
		
		SST_M_ASSERT_EQf((Angle(0.3f) -  0.2f).angle, 0.1f);
		SST_M_ASSERT_EQf((Angle(0.1f) -  0.2f).angle, 0.9f);
		
		SST_M_ASSERT_END;
	}
	
	SST::SimpleTest __Angle("Angle", &_Angle, SST::Required);
	
}