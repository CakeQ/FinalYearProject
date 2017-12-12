#include <stdafx.h>

#include <Game.h>

Game::Game(EngineCore* g_IGameEngine)
{
	g_GameEngine = g_IGameEngine;
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

void Game::SetUpTestScene()
{
	Model* m_NewModel = new Model("assets/meshes/simpleCubeWithNormals.obj");
	s_CurrentScene = new Scene(g_GameEngine);

	Entity e_TestModel;
	Entity e_Player;

	ModelComponent* c_ModelComponent = new ModelComponent;
	c_ModelComponent->m_Model = m_NewModel;

	TransformComponent* c_TransformComponent = new TransformComponent;
	c_TransformComponent->v3_Position = glm::vec3(0.0f, 0.0f, 0.0f);
	c_TransformComponent->q_Orientation = glm::quat(0.0f, 0.0f, 0.0f, 1.0f);
	c_TransformComponent->v3_Scale = glm::vec3(1.0f, 1.0f, 1.0f);

	e_TestModel.AddComponent(c_ModelComponent);
	e_TestModel.AddComponent(c_TransformComponent);

	CameraComponent* c_CameraComponent = new CameraComponent;
	c_CameraComponent->LookAt(c_TransformComponent->GetPosition());
	c_CameraComponent->v3_Position = glm::vec3(0.0f, 0.0f, 4.0f);
	c_CameraComponent->q_Orientation = glm::quat(0.0f, 0.0f, 0.0f, 1.0f);

	c_TransformComponent->v3_Position = glm::vec3(0.0f, 0.0f, 10.0f);
	c_TransformComponent->q_Orientation = glm::quat(0.0f, 0.0f, 0.0f, 1.0f);
	c_TransformComponent->v3_Scale = glm::vec3(1.0f, 1.0f, 1.0f);

	e_Player.AddComponent(c_CameraComponent);
	e_Player.AddComponent(c_TransformComponent);

	s_CurrentScene->vt_EntityList.push_back(e_TestModel);
	s_CurrentScene->vt_EntityList.push_back(e_Player);
	s_CurrentScene->SetCurrentCamera(c_CameraComponent);
}