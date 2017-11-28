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
#include <ModelComponent.h>
#include <Shader.h>

class Game
{
private:
	std::vector<Entity> vt_EntityList;
	Entity e_Player;
	Entity e_Camera;

public:
	EngineCore* g_GameEngine;

	Game();

	void HandleInput(const std::vector<bool>& vt_IKeyBuffer);
	void Update();
	void Draw(Shader* s_IShader);
};