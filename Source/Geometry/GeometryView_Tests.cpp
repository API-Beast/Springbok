//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "GeometryView.h"
#include "../Containers/List.h"
#include <SSTest.h>

namespace
{
	struct Obj
	{
		BoundingRect Bounds;
		bool Check;
		Obj() = default;
	};
	
	void _GeometryView()
	{
		SST_M_ASSERT_START;
		
		List<Obj*> objects = { new Obj{BoundingRect(   0, 32), 1},
													 new Obj{BoundingRect(  80, 32), 1},
													 new Obj{BoundingRect(-400, 32), 0},
													 new Obj{BoundingRect(-200, 32), 1},
													 new Obj{BoundingRect(-216, 32), 1},
													 new Obj{BoundingRect( 600, 32), 0},
													 new Obj{BoundingRect( 800, 32), 0}
												};
		GeometryView<Obj*, BoundingRect, Obj, &Obj::Bounds> view(objects);
		auto foundObjs = view.getObjectsInRect(-200, 100);
		
		for(auto* x : foundObjs)
			SST_M_ASSERT_EQ(x->Check, true);
		
		for(auto* obj : objects)
			delete obj;
		
		SST_M_ASSERT_END;
	}
	
	SST::SimpleTest __GeometryView("GeometryView", &_GeometryView, SST::Required);
	
}