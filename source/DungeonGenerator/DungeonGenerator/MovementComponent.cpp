#include <stdafx.h>

#include <MovementComponent.h>

MovementComponent::MovementComponent(Component* IParentComponent) : Component(IParentComponent)
{

}

void MovementComponent::HandleInput(const std::vector<bool>& KeyBuffer)
{
	if (KeyBuffer[87])
	{
		//GetParent()->Transform(glm::vec3(1.0f, 0.0f, 0.0f));
		std::cout << "w" << std::endl;
	}
	if (KeyBuffer[83])
	{
		//GetParent()->Transform(glm::vec3(-1.0f, 0.0f, 0.0f));
		std::cout << "s" << std::endl;
	}
	if (KeyBuffer[65])
	{
		//GetParent()->Transform(glm::vec3(0.0f, -1.0f, 0.0f));
		std::cout << "a" << std::endl;
	}
	if (KeyBuffer[68])
	{
		//GetParent()->Transform(glm::vec3(1.0f, 1.0f, 0.0f));
		std::cout << "d" << std::endl;
	}
}
