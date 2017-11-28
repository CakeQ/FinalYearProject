#pragma once

class Component
{
private:
	glm::vec3 v3_WorldPos;

public:
	Component() {};
	virtual ~Component() {};

	void Transform(glm::vec3 v3_ITransform);

	virtual void Update() = 0;
	virtual void HandleInput(const std::vector<bool>& vt_IKeyBuffer, const glm::vec2 v2_IMousebuffer) = 0;

	void SetWorldPos(glm::vec3 v3_IWorldPos);
	void SetWorldPos(float f_IX, float f_IY, float f_IZ);
	
	glm::vec3 GetWorldPos() { return v3_WorldPos; };
};