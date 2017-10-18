#pragma once

#include <Entity.h>

class Player : public Entity
{
private:

public:
	Player(glm::vec3 IWorldPos);

	void HandleInput() override;
};