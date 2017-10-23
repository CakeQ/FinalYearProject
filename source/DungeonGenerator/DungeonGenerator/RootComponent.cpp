#include <stdafx.h>

#include <RootComponent.h>

RootComponent::RootComponent(glm::vec3 IWorldPos) : Component(this)
{
	WorldPos = IWorldPos;
}

void RootComponent::AddComponent(Component* IComponent)
{
	ComponentList.push_back(IComponent);
}

Component* RootComponent::GetComponent(int ComponentID)
{
	return nullptr;
}

bool RootComponent::CheckForComponent(int ComponentID)
{
	return false;
}

void RootComponent::Update()
{
	for (Component* IComponent : ComponentList)
	{
		IComponent->Update();
	}
}

void RootComponent::HandleInput(const std::vector<bool>& KeyBuffer)
{
	for (Component* IComponent : ComponentList)
	{
		IComponent->HandleInput(KeyBuffer);
	}
}
