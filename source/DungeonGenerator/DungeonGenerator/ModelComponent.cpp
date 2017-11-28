#include <stdafx.h>

#include <ModelComponent.h>

#include <glm/gtc/type_ptr.hpp>

ModelComponent::ModelComponent(GLchar* c_IPath) : m_MeshModel(c_IPath)
{

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
	glm::mat4 m4_TranslateMatrix = glm::translate(glm::mat4(1.0f), v3_Position);
	glm::mat4 m4_ScaleMatrix = glm::scale(glm::mat4(1.0f), v3_Scale);
	glm::mat4 m4_RotationMatrix = glm::mat4_cast(q_Orientation);
	return m4_TranslateMatrix * m4_ScaleMatrix * m4_RotationMatrix;
}
