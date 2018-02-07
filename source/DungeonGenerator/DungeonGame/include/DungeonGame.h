#pragma once

#include "Game.h"

#include "DungeonInputHandler.h"
#include "DungeonScene.h"

class DungeonGame : public Game
{
public:
	DungeonGame() {};
	~DungeonGame() {};

	void Update(float f_IDeltaTime) override
	{
		if (!s_CurrentScene)
		{
			std::cout << "Error: Scene does not exist!" << std::endl;
			return;
		}

		s_CurrentScene->Update(f_IDeltaTime);
	};

	void Draw() override
	{
		if (!s_CurrentScene)
		{
			std::cout << "Error: Scene does not exist!" << std::endl;
			return;
		}

		s_CurrentScene->Draw();
	};


	void Initialise() override
	{
		SetUpScene();
		s_CurrentScene->ih_InputHandler = new DungeonInputHandler(s_CurrentScene->e_PlayerEntity);
	}

	void SetUpScene() override
	{
		if (s_CurrentScene)
		{
			s_CurrentScene->~Scene();
			s_CurrentScene = nullptr;
		}

		s_CurrentScene = new DungeonScene(e_GameEngine);
		s_CurrentScene->SetUpScene();
	};
};
