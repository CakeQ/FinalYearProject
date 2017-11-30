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
	glm::vec3 v3_Position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::quat q_Orientation = glm::quat(0.0f, 0.0f, 0.0f, 1.0f);
	glm::vec3 v3_Scale = glm::vec3(1.0f, 1.0f, 1.0f);

	ModelComponent(GLchar* c_IPath);

	void Update() override;
	void Draw(Shader* s_IShader);
	void HandleInput(const std::vector<bool>& vt_IKeyBuffer, const glm::vec2 v2_IMousebuffer) override {};
	glm::mat4 GetModelMatrix();
};
