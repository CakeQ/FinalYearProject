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

class Scene
{
private:
	glm::mat4 m4_ProjectionMatrix;
	glm::mat4 m4_ViewMatrix;

public:
	EngineCore* e_GameEngine;
	std::vector<Entity> vt_EntityList;
	Entity e_ActiveEntity;

	Scene(EngineCore* e_IGameEngine);

	void HandleInput(const std::vector<bool>& vt_IKeyBuffer, const glm::vec2 v2_IMousebuffer);
	void Update();
	void Draw(Shader* s_IShaderProgram);

	void SetActiveEntity(Entity e_IEntity);
	Entity GetActiveEntity();
};