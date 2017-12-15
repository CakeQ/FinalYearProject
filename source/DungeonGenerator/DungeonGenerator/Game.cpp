#include <stdafx.h>

#include <Game.h>
#include <TestScene.h>

Game::Game()
{
	g_GameEngine = nullptr;
	s_CurrentScene = nullptr;
}

void Game::HandleInput(const std::vector<bool>& vt_IKeyBuffer, const glm::vec2 v2_IMousebuffer)
{
	if (!s_CurrentScene)
	{
		std::cout << "ERROR: Scene does not exist!" << std::endl;
		return;
	}
	s_CurrentScene->HandleInput(vt_IKeyBuffer, v2_IMousebuffer);
}

void Game::Update()
{
	if (!s_CurrentScene)
	{
		std::cout << "ERROR: Scene does not exist!" << std::endl;
		return;
	}
	s_CurrentScene->Update();
}

void Game::Draw()
{
	if (!s_CurrentScene)
	{
		std::cout << "ERROR: Scene does not exist!" << std::endl;
		return;
	}

	s_CurrentScene->Draw();
}

void Game::SetUpScene()
{
	s_CurrentScene = new TestScene(g_GameEngine);
	s_CurrentScene->SetUpScene();
}