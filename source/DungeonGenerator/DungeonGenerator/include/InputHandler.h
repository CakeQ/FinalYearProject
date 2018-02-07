#pragma once

#include <map>
#include <vector>
#include <iostream>

#include "Entity.h"
#include "TransformComponent.h"


class InputCommand
{
public:
	virtual ~InputCommand() {}
	virtual void Execute(Entity& e_IEntity) = 0;
};

struct InputHandler
{
	Entity* e_AttatchedEntity;

	std::map<int, InputCommand*> m_ControlMapping;

	InputHandler(Entity* e_InputEntity) : e_AttatchedEntity(e_InputEntity) {};

	void handleInputs(const std::vector<bool>& vt_IKeyBuffer, const glm::vec2 v2_IMousePos)
	{
		for (const auto& a_MapEntry : m_ControlMapping)
		{
			if (vt_IKeyBuffer[a_MapEntry.first])
			{
				a_MapEntry.second->Execute(*e_AttatchedEntity);
			}

			if (e_AttatchedEntity->GetComponent<TransformComponent>())
			{
				if (v2_IMousePos.x != 0)
				{
					e_AttatchedEntity->GetComponent<TransformComponent>()->Yaw(v2_IMousePos.x * -0.00025f);
					std::cout << "rotating camera" << std::endl;
				}
			}
			if (e_AttatchedEntity->GetComponent<CameraComponent>())
			{
				if (v2_IMousePos.y > 1) e_AttatchedEntity->GetComponent<CameraComponent>()->Message("LookUp");
				else if (v2_IMousePos.y < -1) e_AttatchedEntity->GetComponent<CameraComponent>()->Message("LookDown");
			}
		}
	};
};