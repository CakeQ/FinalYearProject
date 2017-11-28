#include <stdafx.h>

#include <Game.h>

Game::Game() : e_Player(glm::vec3(0.0f, 0.0f, 0.0f)), e_Camera(glm::vec3(0.0f, 0.0f, 3.0f))
{
	g_GameEngine = nullptr;
	vt_EntityList.push_back(e_Player);
}

void Game::HandleInput(const std::vector<bool>& vt_IKeyBuffer)
{
	e_Player.HandleInput(vt_IKeyBuffer);
}

void Game::Update()
{
	for (Entity e_IEntity : vt_EntityList)
	{
		e_IEntity.Update();
	}
}

void Game::Draw(Shader* s_IShader)
{
	gl::ClearColor(0.0f, 0.3f, 0.3f, 1.0f);
	gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);
	for (Entity e_IEntity : vt_EntityList)
	{
		e_IEntity.Draw(s_IShader);
	}
}