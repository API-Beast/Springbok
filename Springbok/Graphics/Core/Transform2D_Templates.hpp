#include "Transform2D.h"

template<class V>
void Transform2D::transform(V* startVertex, V* endVertex, Vec2F cameraPos) const
{
	for(V* it = startVertex; it < endVertex; ++it)
		it->Position = transformVec2(it->Position, cameraPos);
}