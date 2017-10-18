#include <stdafx.h>

#include <Player.h>
#include <Component.h>
#include <CameraComponent.h>

Player::Player(glm::vec3 IWorldPos) : Entity(IWorldPos)
{
	AddComponent(new CameraComponent(GetWorldPos()));
}

void Player::HandleInput() 
{

}