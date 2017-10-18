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
#include <Input.h>
#include <Entity.h>

class Game
{
private:
	std::vector<Entity*> EntityList;

public:
	EngineCore* GameEngine;
	InputHandler* GameInputHandler;

	Game();

	void Update();
	void Draw();

	void SpawnPlayer();
};