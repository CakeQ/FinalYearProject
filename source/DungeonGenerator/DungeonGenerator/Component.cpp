#include <stdafx.h>

#include <Component.h>

void Component::Transform(glm::vec3 ITransform)
{
	WorldPos += ITransform;
	std::cout << WorldPos.x << " " << WorldPos.y << " " << WorldPos.z << std::endl;
}

void Component::SetWorldPos(glm::vec3 IWorldPos)
{
	WorldPos = IWorldPos;
}

void Component::SetWorldPos(float IX, float IY, float IZ)
{
	WorldPos.x = IX;
	WorldPos.y = IY;
	WorldPos.z = IZ;
}
