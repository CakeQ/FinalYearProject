#include <stdafx.h>

#include <Entity.h>

Entity::Entity(glm::vec3 v3_IWorldPos)
{
	v3_WorldPos = v3_IWorldPos;
}

void Entity::Update()
{
	
}

void Entity::HandleInput(const std::vector<bool>& vt_IKeyBuffer, const glm::vec2 v2_IMousebuffer)
{
	GetComponent<CameraComponent>()->HandleInput(vt_IKeyBuffer, v2_IMousebuffer);
	GetComponent<MovementComponent>()->HandleInput(vt_IKeyBuffer, v2_IMousebuffer);
}