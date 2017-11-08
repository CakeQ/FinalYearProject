#pragma once

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>

#include <Component.h>
#include <Mesh.h>
#include <Model.h>
#include <Shader.h>

class MeshComponent : public Component
{
private:
	GLuint ShaderProgram;

public:
	Model MeshModel;
	glm::vec3 Position;
	glm::quat Orientation;
	glm::vec3 Scale;

	MeshComponent(GLchar* IPath);

	void Update() override;
	void Draw(Shader IShader);
	void HandleInput(const std::vector<bool>& KeyBuffer) override {};
	glm::mat4 GetModelMatrix();
};
