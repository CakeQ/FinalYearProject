#pragma once

class Component
{
private:
	const int ComponentID = 0;
	Component* ParentComponent;

public:
	Component(Component* IParentComponent) { ParentComponent = IParentComponent; };
	virtual ~Component() {};

	virtual void Update() = 0;
	virtual void HandleInput(const std::vector<bool>& KeyBuffer) = 0;

	Component* GetRoot() { return ParentComponent; };
	int GetComponentID() { return ComponentID; };
};