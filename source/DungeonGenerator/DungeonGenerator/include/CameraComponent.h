#pragma once

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Component.h>
#include <Entity.h>

const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SENSITIVTY = 0.25f;
const GLfloat ZOOM = 45.0f;

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

	float f_MouseSensitivity = 0.25f;
	float f_Zoom = 45.0f;

	void UpdateCameraVectors();

public:
	CameraComponent(glm::vec3 v3_IPosition = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 v3_IUp = glm::vec3(0.0f, 1.0f, 0.0f), float f_IPitch = PITCH, float f_IYaw = YAW);
	glm::mat4 GetViewMatrix();

	void Update() override;
	void HandleInput(const std::vector<bool>& KeyBuffer, const glm::vec2 v2_IMousebuffer) override;

	float GetZoom() { return f_Zoom; };
	glm::vec3 GetPosition() { return v3_Position; };
	glm::vec3 GetFront() { return v3_Front; };
};