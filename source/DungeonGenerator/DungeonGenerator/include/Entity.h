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

#include <Component.h>
#include <MeshComponent.h>
#include <Shader.h>

class Entity
{
private:
	glm::vec3 WorldPos;

	std::unordered_map<std::type_index, Component*> ComponentList;

public:
	Entity(glm::vec3 IWorldPos);

	template <typename T>
	void AddComponent(T* IComponent);

	template <typename T>
	T* GetComponent();

	void Update();
	void Draw(Shader IShader);
	void HandleInput(const std::vector<bool>& KeyBuffer);
};