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
#include <Scene.h>

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

	void Update()
	{
		if (!s_CurrentScene)
		{
			std::cout << "ERROR: Scene does not exist!" << std::endl;
			return;
		}
		s_CurrentScene->Update();
	}

	void Draw()
	{
		if (!s_CurrentScene)
		{
			std::cout << "ERROR: Scene does not exist!" << std::endl;
			return;
		}

		s_CurrentScene->Draw();
	}

	void SetUpScene()
	{
		if (s_CurrentScene)
		{
			s_CurrentScene->~Scene();
			s_CurrentScene = nullptr;
		}

		s_CurrentScene = new Scene(e_GameEngine);
	}
};