#include <stdafx.h>

#include <Entity.h>

Entity::Entity(glm::vec3 IWorldPos)
{
	WorldPos = IWorldPos;

	AddComponent(new MeshComponent("../../../assets/meshes/nanosuit.obj"));
}

template <typename T>
void Entity::AddComponent(T* IComponent)
{
	ComponentList[typeid(T)] = IComponent;
}

template <typename T>
T* Entity::GetComponent()
{
	auto Iterator = ComponentList.find(typeid(T));

	if (Iterator != std::end(ComponentList))
	{
		return dynamic_cast<T*>(Iterator->second);
	}

	return nullptr;
}

void Entity::Update()
{

}

void Entity::Draw(Shader IShader)
{
	GetComponent<MeshComponent>()->Draw(IShader);
}

void Entity::HandleInput(const std::vector<bool>& KeyBuffer)
{

}