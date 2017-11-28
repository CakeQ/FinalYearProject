#include <stdafx.h>

#include <Entity.h>

Entity::Entity(glm::vec3 v3_IWorldPos)
{
	v3_WorldPos = v3_IWorldPos;

	AddComponent(new ModelComponent("../../../assets/meshes/simpleCube.obj"));
}

template <typename T>
void Entity::AddComponent(T* t_IComponent)
{
	m_ComponentList[typeid(T)] = t_IComponent;
}

template <typename T>
T* Entity::GetComponent()
{
	auto a_Iterator = m_ComponentList.find(typeid(T));

	if (a_Iterator != std::end(m_ComponentList))
	{
		return dynamic_cast<T*>(a_Iterator->second);
	}

	return nullptr;
}

void Entity::Update()
{

}

void Entity::Draw(Shader* s_IShader)
{
	GetComponent<ModelComponent>()->Draw(s_IShader);
}

void Entity::HandleInput(const std::vector<bool>& vt_IKeyBuffer)
{

}