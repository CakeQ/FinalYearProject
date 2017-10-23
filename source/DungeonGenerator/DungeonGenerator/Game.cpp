#include <stdafx.h>

#include <Game.h>
#include <Player.h>

Game::Game()
{
	GameEngine = nullptr;
	SpawnPlayer();

}

void Game::HandleInput(const std::vector<bool>& KeyBuffer)
{
	PlayerEntity->HandleInput(KeyBuffer);
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
	PlayerEntity = new Player(glm::vec3(0.0f, 0.0f, 10.0f));
	EntityList.push_back(PlayerEntity);
}