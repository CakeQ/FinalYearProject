#include <stdafx.h>

#include <Player.h>
#include <Component.h>
#include <CameraComponent.h>
#include <MovementComponent.h>

Player::Player(glm::vec3 IWorldPos) : Entity(IWorldPos)
{
	ComponentHandler->AddComponent(new CameraComponent(ComponentHandler, ComponentHandler->GetWorldPos()));
	ComponentHandler->AddComponent(new MovementComponent(ComponentHandler));
}