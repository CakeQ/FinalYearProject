/**
* \file Game.h
*/

//! Game controller class.
/*!
Game controller used to handle everything game related.
Created by Daniel Thompson, P15230940.
*/

#pragma once

#include "EngineCoreBase.h"
#include "Scene.h"

class Game
{
public:
	EngineCore* e_GameEngine;
	Scene* s_CurrentScene;

	Game() 
	{
		e_GameEngine = nullptr;
		s_CurrentScene = nullptr;
	};

	virtual void Update(float f_IDeltaTime) = 0;
	virtual void Draw() = 0;
	virtual void SetUpScene() = 0;
	virtual void Initialise() = 0;
};