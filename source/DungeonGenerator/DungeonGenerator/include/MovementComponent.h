#pragma once

#include <map>
#include <vector>

#include <Component.h>
#include <RootComponent.h>

class MovementComponent : public Component
{
private:

public:
	MovementComponent(RootComponent* IParentComponent);

	void Update() override {};
	void HandleInput(const std::vector<bool>& KeyBuffer) override;
};