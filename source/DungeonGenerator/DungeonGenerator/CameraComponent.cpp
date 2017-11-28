#include <stdafx.h>

#include <CameraComponent.h>

CameraComponent::CameraComponent(glm::vec3 v3_IPosition, glm::vec3 v3_IUp, float f_IPitch, float f_IYaw) : v3_Front(glm::vec3(0.0f, 0.0f, -1.0f)), f_MouseSensitivity(SENSITIVTY), f_Zoom(ZOOM)
{
	v3_Position = v3_IPosition;
	v3_WorldUp = v3_IUp;
	f_Pitch = f_IPitch;
	f_Yaw = f_IYaw;

	UpdateCameraVectors();
}

void CameraComponent::UpdateCameraVectors()
{
	glm::vec3 v3_TempFront;
	v3_TempFront.x = cos(glm::radians(f_Yaw)) * cos(glm::radians(f_Pitch));
	v3_TempFront.y = sin(glm::radians(f_Pitch));
	v3_TempFront.z = sin(glm::radians(f_Yaw)) * cos(glm::radians(f_Pitch));
	v3_Front = glm::normalize(v3_TempFront);
	v3_Right = glm::normalize(glm::cross(v3_Front, v3_WorldUp));
	v3_Up = glm::normalize(glm::cross(v3_Right, v3_Front));
}

glm::mat4 CameraComponent::GetViewMatrix()
{
	return glm::lookAt(v3_Position, (v3_Position + v3_Front), v3_Up);
}

void CameraComponent::Update()
{

}

void CameraComponent::HandleInput(const std::vector<bool>& KeyBuffer, const glm::vec2 v2_IMousebuffer)
{
	float f_XOffset = v2_IMousebuffer.x;
	float f_YOffset = v2_IMousebuffer.y;

	f_XOffset *= f_MouseSensitivity;
	f_YOffset *= f_MouseSensitivity;

	f_Yaw += f_XOffset;
	f_Pitch += f_YOffset;

	if (f_Pitch > 89.0f)
	{
		f_Pitch = 89.0f;
	}
	if (f_Pitch < -89.0f)
	{
		f_Pitch = -89.0f;
	}

	UpdateCameraVectors();
}

