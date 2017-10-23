#include <stdafx.h>

#include <Entity.h>

Entity::Entity(glm::vec3 IWorldPos)
{
	ComponentHandler = new RootComponent(IWorldPos);
}

void Entity::Update()
{
	ComponentHandler->Update();
}

void Entity::Draw(GLuint IShaderProgram)
{
	ComponentHandler->Draw(IShaderProgram);
}

void Entity::HandleInput(const std::vector<bool>& KeyBuffer)
{
	ComponentHandler->HandleInput(KeyBuffer);
}
