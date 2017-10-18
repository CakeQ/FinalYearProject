#include <stdafx.h>

#include <Game.h>
#include <Player.h>

Game::Game()
{
	GameEngine = nullptr;
	GameInputHandler = new InputHandler();


}

void Game::Update()
{
	for (Entity* IEntity : EntityList)
	{
		IEntity->Update();
	}
}

void Game::Draw()
{
	GameEngine->Draw();
}

void Game::SpawnPlayer()
{
	EntityList.push_back(new Player(glm::vec3(0.0f,0.0f,10.0f)));
}