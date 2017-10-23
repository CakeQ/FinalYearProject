#pragma once

class Component
{
private:
	const int ComponentID = 0;
	Component* ParentComponent;
	glm::vec3 WorldPos;

public:
	Component(Component* IParentComponent) { ParentComponent = IParentComponent; };
	virtual ~Component() {};

	void Transform(glm::vec3 ITransform);

	virtual void Draw() = 0;
	virtual void Update() = 0;
	virtual void HandleInput(const std::vector<bool>& KeyBuffer) = 0;

	void SetWorldPos(glm::vec3 IWorldPos);
	void SetWorldPos(float IX, float IY, float IZ);
	
	glm::vec3 GetWorldPos() { return WorldPos; };
	Component* GetRoot() { return ParentComponent; };
	int GetComponentID() { return ComponentID; };
};