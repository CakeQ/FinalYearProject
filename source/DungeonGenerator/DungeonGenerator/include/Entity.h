/**
* \file Object.h
*/

//! Parent object class.
/*!
Base object class to which every game object will inherit from.
Created by Daniel Thompson, P15230940.
*/

#pragma once

#include <Component.h>

class Entity
{
private:
	glm::vec3 WorldPos;
	std::vector<Component*> ComponentList;

public:
	Entity(glm::vec3 IWorldPos);

	void AddComponent(Component* IComponent);
	bool CheckForComponent(int ComponentID);
	

	glm::vec3 GetWorldPos() { return WorldPos; };
	Component* GetComponent(int ComponentID);

	void Update();
	virtual void HandleInput() = 0;
};