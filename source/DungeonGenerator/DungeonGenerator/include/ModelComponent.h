#pragma once

#include <vector>

#include <Component.h>
#include <Mesh.h>
#include <Model.h>
#include <Shader.h>

class ModelComponent : public Component
{
private:
	GLuint ui_ShaderProgram;

public:
	Model* m_Model;
	glm::vec3 v3_Position;
	glm::quat q_Orientation;
	glm::vec3 v3_Scale;

	ModelComponent()
	{
		v3_Position = glm::vec3(0.0f, 0.0f, 0.0f);
		v3_Scale = glm::vec3(1.0f, 1.0f, 1.0f);
		q_Orientation = glm::quat(0.0f, 0.0f, 0.0f, 1.0f);
	};

	void Update() override {};
	void HandleInput(const std::vector<bool>& vt_IKeyBuffer, const glm::vec2 v2_IMousebuffer) override {};
};
