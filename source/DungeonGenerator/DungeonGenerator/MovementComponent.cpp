#include <stdafx.h>

#include <MovementComponent.h>

MovementComponent::MovementComponent()
{

}

void MovementComponent::HandleInput(const std::vector<bool>& KeyBuffer)
{
	if (KeyBuffer[87])
	{
		Transform(glm::vec3(1.0f, 0.0f, 0.0f));
	}
	if (KeyBuffer[83])
	{
		Transform(glm::vec3(-1.0f, 0.0f, 0.0f));
	}
	if (KeyBuffer[65])
	{
		Transform(glm::vec3(0.0f, -1.0f, 0.0f));
	}
	if (KeyBuffer[68])
	{
		Transform(glm::vec3(1.0f, 1.0f, 0.0f));
	}
}
