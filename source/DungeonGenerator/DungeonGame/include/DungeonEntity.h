#pragma once

#include "Entity.h"

class Room;

class DungeonEntity : public Entity
{
public:
	int i_State = 0;
	ModelManager* mm_ModelManager;

	DungeonEntity(ModelManager* mm_IModelManager)
	{
		AddComponent(new TransformComponent);
		AddComponent(new ModelComponent);

		mm_ModelManager = mm_IModelManager;
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

	void ChangeState(int i_IState)
	{
		i_State = i_IState;
		ChangeState();
	}
};