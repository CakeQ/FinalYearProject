#include <stdafx.h>

#include <vector>
#include <MeshComponent.h>

MeshComponent::MeshComponent(RootComponent* IParentComponent, GLchar* IPath) : Component(IParentComponent)
{
	MeshModel = new Model(IPath);
}

void MeshComponent::Draw(GLuint IShaderProgram)
{
	MeshModel->Draw(IShaderProgram);
}

void MeshComponent::Update()
{

}
