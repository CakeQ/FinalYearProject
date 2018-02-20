#pragma once

#include "Entity.h"

#include "TransformComponent.h"
#include "ModelComponent.h"
#include "CameraComponent.h"

class PlayerEntity : public Entity
{

public:

	PlayerEntity()
	{
		AddComponent(new TransformComponent);
		AddComponent(new CameraComponent);
	};

	~PlayerEntity()
	{
		m_ComponentList.clear();
	};

	void Update(float f_IDeltaTime) override
	{
		TransformComponent* c_Transform = GetComponent<TransformComponent>();
		GetComponent<CameraComponent>()->v3_Position = -1.0f * (c_Transform->v3_Position + glm::vec3(0.0f, 0.0f, 0.0f));
		GetComponent<CameraComponent>()->q_Orientation = inverse(c_Transform->q_Orientation);
	};

	void Message(const std::string s_IMessage) override
	{

		for (auto c_Component : m_ComponentList)
		{
			c_Component.second->Message(s_IMessage);
		}
	};
};