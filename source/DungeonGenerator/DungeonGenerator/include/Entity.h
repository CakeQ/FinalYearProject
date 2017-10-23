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
#include <RootComponent.h>

class Entity
{
private:
	glm::vec3 WorldPos;

public:
	RootComponent* ComponentHandler;

	Entity(glm::vec3 IWorldPos);
	virtual ~Entity() {};

	void Update();
	void Draw();
	void HandleInput(const std::vector<bool>& KeyBuffer);
};