#include <stdafx.h>

#include <ModelComponent.h>

ModelComponent::ModelComponent(GLchar* c_IPath) : m_MeshModel(c_IPath)
{

}

void ModelComponent::Update()
{

}

void ModelComponent::Draw(Shader* IShader)
{
	m_MeshModel.Draw(IShader);
}

glm::mat4 ModelComponent::GetModelMatrix()
{
	glm::mat4 m4_TranslateMatrix = glm::translate(glm::mat4(1.0f), v3_Position);
	glm::mat4 m4_ScaleMatrix = glm::scale(glm::mat4(1.0f), v3_Scale);
	glm::mat4 m4_RotationMatrix = glm::mat4_cast(q_Orientation);
	return m4_TranslateMatrix * m4_ScaleMatrix * m4_RotationMatrix;
}
