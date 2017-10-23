#pragma once

#include <glm\glm.hpp>
#include <vector>

#include <Component.h>

class CameraComponent : public Component
{
private:
	const int ComponentID = 2;

	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	float Pitch;
	float Yaw;

	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

public:
	CameraComponent(Component* IParentComponent, glm::vec3 IPosition);

	void Draw(GLuint IShaderProgram) override {};
	void Update() override;
	void HandleInput(const std::vector<bool>& KeyBuffer) override {};
};