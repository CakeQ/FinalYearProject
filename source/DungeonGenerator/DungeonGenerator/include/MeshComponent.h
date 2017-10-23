#pragma once

#include <Component.h>
#include <RootComponent.h>
#include <Mesh.h>

class MeshComponent : public Component
{
private:
	const int ComponentID = 1;

	//Mesh* Model;

public:
	MeshComponent(RootComponent* IParentComponent);

	void Draw() override;
	void Update() override;
	void HandleInput(const std::vector<bool>& KeyBuffer) override {};
};