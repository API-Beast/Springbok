#include "Transform2D.h"

template<class V>
void Transform2D::transform(V* startVertex, V* endVertex, Vec2F cameraPos, Vec2F coordinateMult) const
{
	Vec2F minPos(9999999, 9999999);
	Vec2F maxPos;
	Vec2F size;
	
	// Preprocessing
	for(V* it = startVertex; it < endVertex; ++it)
	{
		auto pos = it->Position;
		// Calculate Size for alignment.
		minPos = minPos.upperBound(pos);
		maxPos = maxPos.lowerBound(pos);
	}
	size = maxPos - minPos;
	
	auto calcNewPos = [&](Vec2F position){ return (Matrix.transform(position - size*Alignment) + Offset - cameraPos * Parallaxity) * coordinateMult; };
	
	// And finally transform
	for(V* it = startVertex; it < endVertex; ++it)
		it->Position = calcNewPos(it->Position);
}