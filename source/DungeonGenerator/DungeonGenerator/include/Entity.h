/**
* \file Object.h
*/

//! Parent object class.
/*!
Base object class to which every game object will inherit from.
Created by Daniel Thompson, P15230940.
*/

#pragma once

#include <vector>
#include <Component.h>

class Entity
{
private:
	std::vector<Component*> ComponentList;

public:
	void AddComponent(Component* IComponent);
	bool CheckForComponent(int ComponentID);
	Component* GetComponent(int ComponentID);

	virtual void Update() = 0;
};