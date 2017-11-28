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

class ModelComponent : public Component
{
private:
	GLuint ui_ShaderProgram;

public:
	Model m_MeshModel;
	glm::vec3 v3_Position;
	glm::quat q_Orientation;
	glm::vec3 v3_Scale;

	ModelComponent(GLchar* c_IPath);

	void Update() override;
	void Draw(Shader* s_IShader);
	void HandleInput(const std::vector<bool>& vt_IKeyBuffer) override {};
	glm::mat4 GetModelMatrix();
};
