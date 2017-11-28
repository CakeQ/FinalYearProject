#include <stdafx.h>

#include <Game.h>

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

void Game::Draw(Shader* s_IShaderProgram)
{
	if (!s_CurrentScene)
	{
		std::cout << "ERROR: Scene does not exist!" << std::endl;
		return;
	}
	s_CurrentScene->Draw(s_IShaderProgram);
}

void Game::SetUpTestScene()
{
	s_CurrentScene = new Scene(g_GameEngine);

	Entity e_TestModel(glm::vec3(0.0f, 0.0f, 0.0f));
	Entity e_Player(glm::vec3(0.0f, 0.0f, 4.0f));

	e_TestModel.AddComponent(new ModelComponent("../../../assets/meshes/simpleCube.obj"));

	e_Player.AddComponent(new CameraComponent());
	e_Player.AddComponent(new MovementComponent());

	s_CurrentScene->SetActiveEntity(e_Player);

	s_CurrentScene->vt_EntityList.push_back(e_TestModel);
	s_CurrentScene->vt_EntityList.push_back(e_Player);
}