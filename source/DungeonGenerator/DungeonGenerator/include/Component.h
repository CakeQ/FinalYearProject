#pragma once

class Component
{
private:
	const int ComponentID = 0;

public:
	virtual ~Component() {};

	virtual void Update() = 0;

	int GetComponentID() { return ComponentID; };
};