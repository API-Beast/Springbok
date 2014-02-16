#include "KeyframeList.h"
#include <SSTest.h>

namespace
{

void basicUsage()
{
	KeyframeList<float> frames;
	frames.setInterpolationMethod(Interpolation::Linear);
	frames.insert(0.0f,  0.0f);
	frames.insert(0.5f,  1.0f);
	frames.insert(1.0f, 10.0f);
	
	SST_M_ASSERT_START;
	SST_M_ASSERT_EQ(frames[0.25f], 0.5f);
	SST_M_ASSERT_EQ(frames[0.50f], 1.0f);
	SST_M_ASSERT_EQ(frames[0.75f], 5.5f);
	
	KeyframeList<float> scale = 1.f;
	scale.setInterpolationMethod(Interpolation::Linear);
	scale.insert(0.25, 4.f);
	scale.insert(0.75, 3.f);
	scale.insert(1.00, 4.f);
	
	SST_M_ASSERT_EQ(scale[0.25], 4.0f);
	SST_M_ASSERT_EQ(scale[0.50], 3.5f);
	SST_M_ASSERT_EQ(scale[0.75], 3.0f);
	
	KeyframeList<float> fallback = 1.f;
	SST_M_ASSERT_EQ(fallback[0.00f], 1.0f);
	SST_M_ASSERT_EQ(fallback[0.25f], 1.0f);
	SST_M_ASSERT_EQ(fallback[0.50f], 1.0f);
	SST_M_ASSERT_EQ(fallback[0.75f], 1.0f);
	SST_M_ASSERT_END;
}

	
SST::SimpleTest a("Animation/KeyframeList", &basicUsage,  SST::Required);

}