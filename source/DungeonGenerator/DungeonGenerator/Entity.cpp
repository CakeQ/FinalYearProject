#include <stdafx.h>

#include <Entity.h>

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
