#include <stdafx.h>

#include <Game.h>
#include <PlayerEntity.h>

Game::Game()
{
	GameEngine = nullptr;
	SpawnPlayer();

}

void Game::HandleInput(const std::vector<bool>& KeyBuffer)
{
	Player->HandleInput(KeyBuffer);
}

void Game::Update()
{
	for (Entity* IEntity : EntityList)
	{
		IEntity->Update();
	}
}

void Game::Draw(GLuint IShaderProgram)
{
	for (Entity* IEntity : EntityList)
	{
		IEntity->Draw(IShaderProgram);
	}
}

void Game::SpawnPlayer()
{
	Player = new PlayerEntity(glm::vec3(0.0f, 0.0f, -10.0f));
	EntityList.push_back(Player);
}