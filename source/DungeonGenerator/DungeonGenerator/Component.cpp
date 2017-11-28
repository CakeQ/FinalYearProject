#include <stdafx.h>

#include <Component.h>

void Component::Transform(glm::vec3 v3_ITransform)
{
	v3_WorldPos += v3_ITransform;
}

void Component::SetWorldPos(glm::vec3 v3_IWorldPos)
{
	v3_WorldPos = v3_IWorldPos;
}

void Component::SetWorldPos(float f_IX, float f_IY, float f_IZ)
{
	v3_WorldPos.x = f_IX;
	v3_WorldPos.y = f_IY;
	v3_WorldPos.z = f_IZ;
}
