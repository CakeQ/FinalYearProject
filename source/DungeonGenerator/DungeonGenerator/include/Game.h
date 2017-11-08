/**
* \file Game.h
*/

//! Game controller class.
/*!
Game controller used to handle everything game related.
Created by Daniel Thompson, P15230940.
*/

#pragma once

#include <EngineCoreBase.h>
#include <Entity.h>
#include <Component.h>
#include <MeshComponent.h>
#include <Shader.h>

class Game
{
private:
	std::vector<Entity> EntityList;
	Entity Player;
	Entity Camera;

public:
	EngineCore* GameEngine;

	Game();

	void HandleInput(const std::vector<bool>& KeyBuffer);
	void Update();
	void Draw(Shader IShader);
};