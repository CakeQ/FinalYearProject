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
	CameraComponent* c_CurrentCamera;

public:
	EngineCore* e_GameEngine;
	std::vector<Entity> vt_EntityList;

	Scene(EngineCore* e_IGameEngine);

	void SetCurrentCamera(CameraComponent* c_ICamera) { c_CurrentCamera = c_ICamera; };

	void HandleInput(const std::vector<bool>& vt_IKeyBuffer, const glm::vec2 v2_IMousebuffer) {};
	void Update();
	void Draw();
};