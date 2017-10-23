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

class Game
{
private:
	std::vector<Entity*> EntityList;
	Entity* PlayerEntity;

public:
	EngineCore* GameEngine;

	Game();

	void HandleInput(const std::vector<bool>& KeyBuffer);
	void Update();
	void Draw();

	void SpawnPlayer();
};