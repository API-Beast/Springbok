#include "BoundingShapes.h"
#include <SSTest.h>

namespace
{
	void _BoundingShapes()
	{
		SST_M_ASSERT_START;
		SST_M_ASSERT( IsIntersecting(BoundingRect{Vec2F(  50,   0),  Vec2F(100, 100)}, BoundingRect{Vec2F(0, 0), Vec2F(100, 100)}));
		SST_M_ASSERT(!IsIntersecting(BoundingRect{Vec2F( 100, 100),  Vec2F(100, 100)}, BoundingRect{Vec2F(0, 0), Vec2F(100, 100)}));
		SST_M_ASSERT(!IsIntersecting(BoundingRect{Vec2F(- 10,   0), -Vec2F(100, 100)}, BoundingRect{Vec2F(0, 0), Vec2F(100, 100)}));
		SST_M_ASSERT(!IsIntersecting(BoundingRect{Vec2F(-150,   0),  Vec2F(100, 100)}, BoundingRect{Vec2F(0, 0), Vec2F(100, 100)}));
		SST_M_ASSERT_END;
	}
	
	SST::SimpleTest __BoundingShapes("BoundingShapes", &_BoundingShapes, SST::Required);
	
}