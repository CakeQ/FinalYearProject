#pragma once

#include <map>
#include <vector>

#include <Component.h>

class MovementComponent : public Component
{
private:

public:
	MovementComponent();

	void Update() override {};
	void HandleInput(const std::vector<bool>& vt_IKeyBuffer) override;
};