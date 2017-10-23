#include <stdafx.h>

#include <RootComponent.h>

RootComponent::RootComponent(glm::vec3 IWorldPos) : Component(this)
{
	SetWorldPos(IWorldPos);
}

void RootComponent::AddComponent(Component* IComponent)
{
	ComponentList.push_back(IComponent);
}

Component* RootComponent::GetComponent(int IComponentID)
{
	if (CheckForComponent(IComponentID))
	{
		for (Component* IteratorComponent : ComponentList)
		{
			if (IteratorComponent->GetComponentID() == IComponentID)
			{
				return IteratorComponent;
			}
		}
	}
	return nullptr;
}

bool RootComponent::CheckForComponent(int IComponentID)
{
	for (Component* IteratorComponent : ComponentList)
	{
		if (IteratorComponent->GetComponentID() == IComponentID)
		{
			return true;
		}
	}
	return false;
}

void RootComponent::Draw(GLuint IShaderProgram)
{
	if (CheckForComponent(3))
	{
		GetComponent(3)->Draw(IShaderProgram);
	}
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
