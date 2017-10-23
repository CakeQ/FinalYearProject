#pragma once

#include <map>
#include <vector>

#include <Component.h>
#include <RootComponent.h>

class MovementComponent : public Component
{
private:
	const int ComponentID = 3;

public:
	MovementComponent(RootComponent* IParentComponent);

	void Draw() override {};
	void Update() override {};
	void HandleInput(const std::vector<bool>& KeyBuffer) override;
};