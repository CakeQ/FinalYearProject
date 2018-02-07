/**
* \file Object.h
*/

//! Parent object class.
/*!
Base object class to which every game object will inherit from.
Created by Daniel Thompson, P15230940.
*/

#pragma once

#include <unordered_map>
#include <typeindex>

#include "Component.h"
#include "ModelComponent.h"
#include "CameraComponent.h"
#include "Shader.h"

class Entity
{
public:
	std::unordered_map<std::type_index, Component*> m_ComponentList;

	template <typename T>
	void AddComponent(T* t_IComponent)
	{
		m_ComponentList[typeid(T)] = t_IComponent;
	}

	template <typename T>
	T* GetComponent()
	{
		auto a_Iterator = m_ComponentList.find(typeid(T));

		if (a_Iterator != std::end(m_ComponentList))
		{
			return dynamic_cast<T*>(a_Iterator->second);
		}

		return nullptr;
	}

	virtual void Update(float f_IDeltaTime) = 0;
	virtual void Message(const std::string s_IMessage) = 0;
};