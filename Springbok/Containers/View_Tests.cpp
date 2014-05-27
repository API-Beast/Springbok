#include "View.h"
#include "../Procedural/RandomNumberGenerator.h"
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
		view.update();
		
		SST_M_ASSERT_EQ(view[11], 11);
		SST_M_ASSERT_EQ(view[12], 12);
		
		SST_M_ASSERT_EQ(view.findIndex(4), 4);
		SST_M_ASSERT_EQ(view.findIndex(7), 7);
		SST_M_ASSERT_EQ(view.findIndex(22), 12);
		
		SST_M_ASSERT_END;
	}
	
	void ptr()
	{
		int x[] = {6, 2, 4};
		List<int*> data = {x, x+1, x+2};
		SortedView<int*> view(data);
		SST_M_ASSERT_START;
		SST_M_ASSERT_EQ(*view[0], 2);
		SST_M_ASSERT_EQ(*view[1], 4);
		SST_M_ASSERT_EQ(*view[2], 6);
		SST_M_ASSERT_END;
	}
	
	void reliability()
	{
		RandomNumberGenerator RNG(3489034, 4239012);
		List<int> data(4096);
		SortedView<int> view(data);
		
		for(int i = 1; i < 2000; ++i)
		{
			float action = RNG.getFloat();
			if(action < 0.25f)
			{
				if(data.UsedLength)
					data.quickRemove(RNG.getNumber(data.UsedLength));
			}
			else if(action < 0.50f)
			{
				if(data.UsedLength)
					data[RNG.getNumber(data.UsedLength)] = RNG.getNumber(10000);
			}
			else
				data.pushBack(RNG.getNumber(10000));
			
			if((i % 512) == 0)
			{
				view.update();
				List<int> set(128);
				int lastItem = -999;
				for(int point : Subrange(view.Data, Max(view.Data.UsedLength-10000, 0), view.Data.UsedLength))
				{
					if(set.findIndex(point)!=-1)
						throw "Double index";
					if(data[point] < lastItem)
						throw "Out of order";
					set.pushBack(point);
					lastItem = data[point];
				}
			}
		}
	};
	
	SST::SimpleTest _View_reliability("View::reliability", &reliability, SST::Required);
	SST::SimpleTest _View_ptr("View::ptr", &ptr, SST::Required);
	SST::SimpleTest __View("View", &_View, SST::Required);
	
}