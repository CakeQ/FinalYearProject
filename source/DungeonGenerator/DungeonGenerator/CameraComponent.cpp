#include <stdafx.h>

#include <CameraComponent.h>

CameraComponent::CameraComponent(Component* IParentComponent, glm::vec3 IPosition) : Component(IParentComponent)
{
	Position = IPosition;
}

void CameraComponent::Update()
{

}