#pragma once

#include <Component.h>
#include <RootComponent.h>
#include <Mesh.h>
#include <Model.h>

class MeshComponent : public Component
{
private:
	const int ComponentID = 1;

	Model* MeshModel;
	GLuint ShaderProgram;

public:
	MeshComponent(RootComponent* IParentComponent, GLchar* IPath);

	void Draw(GLuint IShaderProgram) override;
	void Update() override;
	void HandleInput(const std::vector<bool>& KeyBuffer) override {};
};