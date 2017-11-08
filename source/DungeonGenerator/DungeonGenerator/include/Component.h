#pragma once

class Component
{
private:
	glm::vec3 WorldPos;

public:
	Component() {};
	virtual ~Component() {};

	void Transform(glm::vec3 ITransform);

	virtual void Update() = 0;
	virtual void HandleInput(const std::vector<bool>& KeyBuffer) = 0;

	void SetWorldPos(glm::vec3 IWorldPos);
	void SetWorldPos(float IX, float IY, float IZ);
	
	glm::vec3 GetWorldPos() { return WorldPos; };
};