#include <stdafx.h>

#include <ModelComponent.h>

#include <glm/gtc/type_ptr.hpp>

ModelComponent::ModelComponent(GLchar* c_IPath) : m_MeshModel(c_IPath)
{
	v3_Position = glm::vec3(0.0f, 0.0f, 0.0f);
	v3_Scale = glm::vec3(1.0f, 1.0f, 1.0f);
	q_Orientation = glm::quat(0.0f, 0.0f, 0.0f, 1.0f);

	std::cout << v3_Position.x << std::endl;
	std::cout << v3_Scale.x << std::endl;
	std::cout << q_Orientation.x << std::endl;
}

void ModelComponent::Update()
{

}

void ModelComponent::Draw(Shader* s_IShaderProgram)
{
	gl::UniformMatrix4fv(gl::GetUniformLocation(s_IShaderProgram->ui_ShaderProgram, "model"), 1, gl::FALSE_, glm::value_ptr(GetModelMatrix()));
	m_MeshModel.Draw(s_IShaderProgram);
}

glm::mat4 ModelComponent::GetModelMatrix()
{
	glm::mat4 m4_ModelMatrix;
	m4_ModelMatrix = glm::translate(m4_ModelMatrix, v3_Position);
	m4_ModelMatrix = glm::scale(m4_ModelMatrix, v3_Scale);
	m4_ModelMatrix = glm::mat4_cast(q_Orientation);
	return m4_ModelMatrix;
}
