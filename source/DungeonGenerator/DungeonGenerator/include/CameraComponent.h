#pragma once

#include <glm\glm.hpp>
#include <vector>

#include <Component.h>

class CameraComponent : public Component
{
private:
	glm::vec3 v3_Position;
	glm::vec3 v3_Front;
	glm::vec3 v3_Up;
	glm::vec3 v3_Right;
	glm::vec3 v3_WorldUp;

	float f_Pitch;
	float f_Yaw;

	float f_MovementSpeed;
	float f_MouseSensitivity;
	float f_Zoom;

public:
	CameraComponent();

	void Update() override;
	void HandleInput(const std::vector<bool>& KeyBuffer) override {};
};