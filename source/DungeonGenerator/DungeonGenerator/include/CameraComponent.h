#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

#include <iostream>

#include "Component.h"

class CameraComponent : public Component
{
public:
	glm::vec3 v3_Position;
	glm::quat q_Orientation;

	float f_FOV;

	CameraComponent() : v3_Position(0), q_Orientation(1, 0, 0, 0), f_FOV(45) {};
	CameraComponent(const glm::vec3& v3_IPos) : v3_Position(v3_IPos), q_Orientation(1, 0, 0, 0), f_FOV(45) {};
	CameraComponent(const glm::vec3& v3_IPos, const glm::quat& q_IOrient) : v3_Position(v3_IPos), q_Orientation(q_IOrient), f_FOV(45) {};

	void LookAt(const glm::vec3& v3_ITarget) { q_Orientation = (glm::toQuat(glm::lookAt(v3_Position, v3_ITarget, glm::vec3(0, 1, 0)))); } // Doesn't work

	glm::mat4 GetViewMatrix() const { return glm::translate(glm::mat4_cast(q_Orientation), v3_Position); }

	const glm::vec3& GetPosition() const { return v3_Position; }
	const glm::quat& GetOrientation() const { return q_Orientation; }

	void Translate(const glm::vec3 &v) { v3_Position += v * q_Orientation; }
	void Translate(float f_IX, float f_IY, float f_IZ) { v3_Position += glm::vec3(f_IX, f_IY, f_IZ) * q_Orientation; }

	void Rotate(float f_IAngle, const glm::vec3 &axis) { q_Orientation *= glm::angleAxis(f_IAngle, axis * q_Orientation); }
	void Rotate(float f_IAngle, float f_IX, float f_IY, float f_IZ) { q_Orientation *= glm::angleAxis(f_IAngle, glm::vec3(f_IX, f_IY, f_IZ) * q_Orientation); }

	void Yaw(float f_IAngle) { Rotate(f_IAngle, 0.0f, 1.0f, 0.0f); }
	void Pitch(float f_IAngle) { Rotate(f_IAngle, 1.0f, 0.0f, 0.0f); }
	void Roll(float f_IAngle) { Rotate(f_IAngle, 0.0f, 0.0f, 1.0f); }

	void SetFOV(float f_IFOV) { f_FOV = f_IFOV; }

	void Update() override 
	{
		if (q_Orientation.y > 85.0f) q_Orientation.y = 85.0f;
		if (q_Orientation.y < -85.0f) q_Orientation.y = -85.0f;
		std::cout << v3_Position.x << ", " << v3_Position.y << ", " << v3_Position.z << std::endl;
	};

	void Message(const std::string s_IMessage) override
	{
		if (s_IMessage.compare(0, 4, "Look") == 0)
		{
			float TranslationAngle = 0;

			if (s_IMessage == "LookUp")TranslationAngle = -10;
			else if (s_IMessage == "LookDown")TranslationAngle = 10;
			Pitch(TranslationAngle);
		}
	};
};