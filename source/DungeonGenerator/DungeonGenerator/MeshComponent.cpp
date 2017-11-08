#include <stdafx.h>

#include <MeshComponent.h>

MeshComponent::MeshComponent(GLchar* IPath) : MeshModel(IPath)
{
	std::cout << "Set up model" << std::endl;
}

void MeshComponent::Update()
{

}

void MeshComponent::Draw(Shader IShader)
{
	MeshModel.Draw(IShader);
}

glm::mat4 MeshComponent::GetModelMatrix()
{
	glm::mat4 TranslateMatrix = glm::translate(glm::mat4(1.0f), Position);
	glm::mat4 ScaleMatrix = glm::scale(glm::mat4(1.0f), Scale);
	glm::mat4 RotationMatrix = glm::mat4_cast(Orientation);
	return TranslateMatrix * ScaleMatrix * RotationMatrix;
}
