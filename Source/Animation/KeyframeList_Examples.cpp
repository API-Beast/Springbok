#include "KeyframeList.h"
#include <SSTest.h>

namespace
{

void basicUsage()
{
	KeyframeList<float> frames;
	frames[0.00f].insert( 0.0f);
	frames[0.50f].insert( 1.0f);
	frames[1.00f].insert(10.0f);
	
	/*frames[0.80f].insert(18.0f);
	// oops, we didn't want that keyframe, delete it again
	frames[0.80f].remove();*/
	
	float valueA = frames[0.25f];
	float valueB = frames[0.50f];
	float valueC = frames[0.75f];
	// valueA == 0.5f
	// valueB == 1.0f
	// valueC == 5.5f
	
	SST_M_ASSERT_START;
	SST_M_ASSERT(valueA == 0.5f);
	SST_M_ASSERT(valueB == 1.0f);
	SST_M_ASSERT(valueC == 5.5f);
	SST_M_ASSERT_END;
}

	
SST::SimpleTest a("Animation/KeyframeList", &basicUsage,  SST::Required);

}