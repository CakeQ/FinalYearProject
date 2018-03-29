#pragma once

#include "Entity.h"

class DungeonEntity : public Entity
{
public:
	DungeonEntity()
	{
		AddComponent(new TransformComponent);
		AddComponent(new ModelComponent);
	}

	~DungeonEntity()
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

	virtual void CalculateState() = 0;
	virtual void ChangeState() = 0;
};