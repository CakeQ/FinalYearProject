#include <stdafx.h>

#include <PlayerEntity.h>
#include <Component.h>
#include <CameraComponent.h>
#include <MovementComponent.h>
#include <MeshComponent.h>

PlayerEntity::PlayerEntity(glm::vec3 IWorldPos) : Entity(IWorldPos)
{
	ComponentHandler->AddComponent(new CameraComponent(ComponentHandler, ComponentHandler->GetWorldPos()));
	ComponentHandler->AddComponent(new MovementComponent(ComponentHandler));
	MeshComponent* Mesh = new MeshComponent(ComponentHandler, "../../../assets/meshes/Original-LP.obj");
	ComponentHandler->AddComponent(Mesh);
}