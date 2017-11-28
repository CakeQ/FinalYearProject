#include <stdafx.h>

#include <Scene.h>

Scene::Scene(EngineCore * e_IGameEngine) : e_ActiveEntity(glm::vec3(0.0f, 0.0f, 4.0f))
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
	for (Entity e_IEntity : vt_EntityList)
	{
		gl::UniformMatrix4fv(gl::GetUniformLocation(s_IShaderProgram->ui_ShaderProgram, "model"), 1, gl::FALSE_, glm::value_ptr(e_IEntity.GetComponent<ModelComponent>()->GetModelMatrix()));
	
		e_IEntity.GetComponent<ModelComponent>()->Draw(s_IShaderProgram);
	}
}

void Scene::SetActiveEntity(Entity e_IEntity)
{
	e_ActiveEntity = e_IEntity;

	CameraComponent* c_Camera = e_IEntity.GetComponent<CameraComponent>();
	glm::mat4 Proj = glm::perspective(c_Camera->GetZoom, (e_GameEngine->i_Width / e_GameEngine->i_Height), 0.1f, 100.0f);		//!< Creates projection matrix.
	gl::UniformMatrix4fv(gl::GetUniformLocation(s_ShaderProgram->ui_ShaderProgram, "projection"), 1, 0, glm::value_ptr(Proj));	//!< Sets projection matrix.

	glm::mat4 View = glm::lookAt(glm::vec3(0.0f, 0.0f, 4.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));		//!< Creates view matrix.
	gl::UniformMatrix4fv(gl::GetUniformLocation(s_ShaderProgram->ui_ShaderProgram, "view"), 1, 0, glm::value_ptr(View));		//!< Sets view matrix.
}
