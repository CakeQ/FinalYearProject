#pragma once

#include <Component.h>

class TransformComponent : public Component
{
public:
	glm::vec3 v3_Position;
	glm::quat q_Orientation;
	glm::vec3 v3_Scale;

	TransformComponent() : v3_Position(0), q_Orientation(1, 0, 0, 0), v3_Scale(1.0f) {};
	TransformComponent(const glm::vec3& pos) : v3_Position(pos), q_Orientation(1, 0, 0, 0), v3_Scale(1.0f) {}
	TransformComponent(const glm::vec3& pos, const glm::quat& orient) : v3_Position(pos), q_Orientation(orient), v3_Scale(1.0f) {}
	TransformComponent(const glm::vec3& pos, const glm::quat& orient, const glm::vec3& scale) : v3_Position(pos), q_Orientation(orient), v3_Scale(scale) {}

	const glm::vec3& GetPosition() const { return v3_Position; }
	const glm::quat& GetOrientation() const { return q_Orientation; }
	const glm::vec3& GetScale() const { return v3_Scale; }

	glm::mat4 TransformComponent::GetModelMatrix()
	{
		glm::mat4 m4_TranslationMatrix = glm::translate(glm::mat4(1.0f), v3_Position);
		glm::mat4 m4_ScaleMatrix = glm::scale(glm::mat4(1.0f), v3_Scale);
		glm::mat4 m4_RotationMatrix = glm::mat4_cast(q_Orientation);
		return m4_TranslationMatrix * m4_ScaleMatrix * m4_RotationMatrix;
	}

	void Translate(const glm::vec3 &v3_IOffset) { v3_Position += v3_IOffset; }
	void Translate(float f_IX, float f_IY, float f_IZ) { v3_Position += glm::vec3(f_IX, f_IY, f_IZ) * q_Orientation; }

	void Rotate(float f_IAngle, const glm::vec3 &axis) { q_Orientation *= glm::angleAxis(f_IAngle, axis * q_Orientation); }
	void Rotate(float f_IAngle, float f_IX, float f_IY, float f_IZ) { q_Orientation *= glm::angleAxis(f_IAngle, glm::vec3(f_IX, f_IY, f_IZ) * q_Orientation); }

	void ScaleUp(const glm::vec3 &v3_IScale) { v3_Scale += v3_IScale; }
	void ScaleUp(float f_IX, float f_IY, float f_IZ) { v3_Scale += glm::vec3(f_IX, f_IY, f_IZ); }

	void Yaw(float f_IAngle) { Rotate(f_IAngle, 0.0f, 1.0f, 0.0f); }
	void Pitch(float f_IAngle) { Rotate(f_IAngle, 1.0f, 0.0f, 0.0f); }
	void Roll(float f_IAngle) { Rotate(f_IAngle, 0.0f, 0.0f, 1.0f); }

	void Update() override {};
	void HandleInput(const std::vector<bool>& vt_IKeyBuffer, const glm::vec2 v2_IMousebuffer) override {};
};