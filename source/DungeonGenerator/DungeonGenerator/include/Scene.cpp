#include <stdafx.h>

#include <Scene.h>

Scene::Scene(EngineCore* e_IGameEngine) : e_ActiveEntity(glm::vec3(0.0f, 0.0f, 4.0f))
{
	e_GameEngine = e_IGameEngine;
}

void Scene::HandleInput(const std::vector<bool>& vt_IKeyBuffer, const glm::vec2 v2_IMousebuffer)
{
	e_ActiveEntity.HandleInput(vt_IKeyBuffer, v2_IMousebuffer);
}

void Scene::Update()
{
	for (Entity e_IEntity : vt_EntityList)
	{
		e_IEntity.Update();
	}
}

void Scene::Draw(Shader* s_IShaderProgram)
{
	CameraComponent* c_Camera = e_ActiveEntity.GetComponent<CameraComponent>();
	m4_ViewMatrix = c_Camera->GetViewMatrix();
	gl::UniformMatrix4fv(gl::GetUniformLocation(s_IShaderProgram->ui_ShaderProgram, "projection"), 1, gl::FALSE_, glm::value_ptr(m4_ProjectionMatrix));
	gl::UniformMatrix4fv(gl::GetUniformLocation(s_IShaderProgram->ui_ShaderProgram, "view"), 1, gl::FALSE_, glm::value_ptr(m4_ViewMatrix));

	for (Entity e_IEntity : vt_EntityList)
	{	
		e_IEntity.GetComponent<ModelComponent>()->Draw(s_IShaderProgram);
	}
}

void Scene::SetActiveEntity(Entity e_IEntity)
{
	e_ActiveEntity = e_IEntity;

	CameraComponent* c_Camera = e_ActiveEntity.GetComponent<CameraComponent>();
	m4_ProjectionMatrix = glm::perspective(c_Camera->GetZoom(), (float)e_GameEngine->i_Width / (float)e_GameEngine->i_Height, 0.1f, 100.0f);
}

Entity Scene::GetActiveEntity()
{
	return e_ActiveEntity;
}