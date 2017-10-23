#pragma once

#include <vector>

#include <Component.h>

class RootComponent : public Component
{
private:
	const int ComponentID = 1;
	std::vector<Component*> ComponentList;

public:
	RootComponent(glm::vec3 IWorldPos);

	void AddComponent(Component* IComponent);
	Component* GetComponent(int ComponentID);
	bool CheckForComponent(int ComponentID);

	void Draw(GLuint IShaderProgram);
	void Update() override;
	void HandleInput(const std::vector<bool>& KeyBuffer) override;
};