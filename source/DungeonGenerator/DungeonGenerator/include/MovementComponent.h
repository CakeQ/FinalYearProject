#pragma once

#include <map>
#include <vector>

#include <Component.h>

class MovementComponent : public Component
{
private:

public:
	MovementComponent(Component* IParentComponent);

	void Update() override {};
	void HandleInput(const std::vector<bool>& KeyBuffer) override;
};