#pragma once

#include "Entity.h"

#include "TransformComponent.h"
#include "ModelComponent.h"

class StaticEntity : public Entity
{
public:
	StaticEntity()
	{
		AddComponent(new TransformComponent);
		AddComponent(new ModelComponent);
	};

	~StaticEntity()
	{
		m_ComponentList.clear();
	};

	void Update(float f_IDeltaTime) override
	{
		for (auto a_Iterator = m_ComponentList.begin(); a_Iterator != m_ComponentList.end(); a_Iterator++)
		{
			a_Iterator->second->Update(f_IDeltaTime);
		}
	};

	void Message(const std::string s_IMessage) override {};
};