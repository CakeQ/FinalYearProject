#pragma once

#include <vector>

#include <json/json.h>
#include <glm/detail/type_vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <EngineCoreBase.h>
#include <Entity.h>
#include <Component.h>
#include <CameraComponent.h>
#include <ModelComponent.h>
#include <MovementComponent.h>
#include <TransformComponent.h>

class Scene
{
private:
	CameraComponent c_CurrentCamera;

public:
	EngineCore* e_GameEngine;
	std::vector<Entity> vt_EntityList;

	Scene(EngineCore* e_IGameEngine) { e_GameEngine = e_IGameEngine; };

	void SetCurrentCamera(CameraComponent* c_ICamera) 
	{ 
		c_CurrentCamera.v3_Position = c_ICamera->v3_Position;
		c_CurrentCamera.q_Orientation = c_ICamera->q_Orientation;
		c_CurrentCamera.f_FOV = c_ICamera->f_FOV;
	};

	void HandleInput(const std::vector<bool>& vt_IKeyBuffer, const glm::vec2 v2_IMousebuffer) {};
	
	void Update()
	{
		for (Entity e_IEntity : vt_EntityList)
		{
			e_IEntity.Update();
		}
	};

	void Draw() 
	{
		e_GameEngine->RenderColouredBackground(0.0f, 0.0f, 0.0f);

		e_GameEngine->SetCamera(&c_CurrentCamera);

		for (Entity e_IEntity : vt_EntityList)
		{
			if (e_IEntity.GetComponent<ModelComponent>())
			{
				e_GameEngine->DrawModel(e_IEntity.GetComponent<ModelComponent>()->m_Model, e_IEntity.GetComponent<TransformComponent>()->GetModelMatrix());
			}
		}
	};

	virtual void SetUpScene() = 0;
};