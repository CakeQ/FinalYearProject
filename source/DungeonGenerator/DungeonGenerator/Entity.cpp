#include <stdafx.h>

#include <Entity.h>

Entity::Entity(glm::vec3 IWorldPos)
{
	WorldPos = IWorldPos;
}

void Entity::AddComponent(Component* IComponent)
{
	ComponentList.push_back(IComponent);
}

bool Entity::CheckForComponent(int IComponentID)
{
	for (Component* IComponent : ComponentList)
	{
		if (IComponent->GetComponentID() == IComponentID)
		{ 
			return true;
		}
	}

	return false;
}

Component* Entity::GetComponent(int IComponentID)
{
	if (CheckForComponent(IComponentID))
	{
		for (Component* IComponent : ComponentList)
		{
			if (IComponent->GetComponentID() == IComponentID)
			{
				return IComponent;
			}
		}
	}
	return nullptr;
}

void Entity::Update()
{
	for (Component* IComponent : ComponentList)
	{
		IComponent->Update();
	}
}
