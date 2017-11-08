#include <stdafx.h>

#include <Game.h>

Game::Game() : Player(glm::vec3(0.0f, 0.0f, -10.0f)), Camera(glm::vec3(0.0f, 0.0f, 3.0f))
{
	GameEngine = nullptr;
	EntityList.push_back(Player);
}

void Game::HandleInput(const std::vector<bool>& KeyBuffer)
{
	Player.HandleInput(KeyBuffer);
}

void Game::Update()
{
	for (Entity IEntity : EntityList)
	{
		IEntity.Update();
	}
}

void Game::Draw(Shader IShader)
{
	gl::ClearColor(0.0f, 0.3f, 0.3f, 1.0f);
	for (Entity IteratorObject : EntityList)
	{
		IteratorObject.Draw(IShader);
	}
}