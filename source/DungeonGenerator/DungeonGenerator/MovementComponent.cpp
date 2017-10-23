#include <stdafx.h>

#include <MovementComponent.h>

MovementComponent::MovementComponent(RootComponent* IParentComponent) : Component(IParentComponent)
{

}

void MovementComponent::HandleInput(const std::vector<bool>& KeyBuffer)
{
	if (KeyBuffer[87])
	{
		//GetRoot()->Transform(glm::vec3(1.0f, 0.0f, 0.0f));
	}
	if (KeyBuffer[83])
	{
		//GetRoot()->Transform(glm::vec3(-1.0f, 0.0f, 0.0f));
	}
	if (KeyBuffer[65])
	{
		//GetRoot()->Transform(glm::vec3(0.0f, -1.0f, 0.0f));
	}
	if (KeyBuffer[68])
	{
		//GetRoot()->Transform(glm::vec3(1.0f, 1.0f, 0.0f));
	}
}
