#include "View.h"
#include <SSTest.h>

namespace
{
	void _View()
	{
		SST_M_ASSERT_START;
		
		List<int> data = {5, 6, 7, 8, 9, 10, 0, 1, 2, 3, 4};
		SortedView<int> view(data);
		
		SST_M_ASSERT_EQ(view[0], 0);
		SST_M_ASSERT_EQ(view[1], 1);
		SST_M_ASSERT_EQ(view[2], 2);
		SST_M_ASSERT_EQ(view[3], 3);
		SST_M_ASSERT_EQ(view[4], 4);
		SST_M_ASSERT_EQ(view[5], 5);
		SST_M_ASSERT_EQ(view[6], 6);
		SST_M_ASSERT_EQ(view[7], 7);
		SST_M_ASSERT_EQ(view[8], 8);
		SST_M_ASSERT_EQ(view[9], 9);
		SST_M_ASSERT_EQ(view[10], 10);
		
		data.pushBack(12);
		data.pushBack(11);
		
		SST_M_ASSERT_EQ(view[11], 11);
		SST_M_ASSERT_EQ(view[12], 12);
		
		SST_M_ASSERT_EQ(view.findIndex(4), 4);
		SST_M_ASSERT_EQ(view.findIndex(7), 7);
		SST_M_ASSERT_EQ(view.findIndex(22), 12);
		
		SST_M_ASSERT_END;
	}
	
	SST::SimpleTest __View("View", &_View, SST::Required);
	
}