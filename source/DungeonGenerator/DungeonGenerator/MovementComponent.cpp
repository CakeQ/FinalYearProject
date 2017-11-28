#include <stdafx.h>

#include <MovementComponent.h>

MovementComponent::MovementComponent()
{

}

void MovementComponent::HandleInput(const std::vector<bool>& vt_IKeyBuffer, const glm::vec2 v2_IMousebuffer)
{
	if (vt_IKeyBuffer[87])
	{
		Transform(glm::vec3(1.0f, 0.0f, 0.0f));
	}
	if (vt_IKeyBuffer[83])
	{
		Transform(glm::vec3(-1.0f, 0.0f, 0.0f));
	}
	if (vt_IKeyBuffer[65])
	{
		Transform(glm::vec3(0.0f, -1.0f, 0.0f));
	}
	if (vt_IKeyBuffer[68])
	{
		Transform(glm::vec3(1.0f, 1.0f, 0.0f));
	}
}
