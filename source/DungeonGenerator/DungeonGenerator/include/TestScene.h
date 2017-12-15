#pragma once

#include <Scene.h>

class TestScene : public Scene
{
public:
	TestScene(EngineCore* e_IGameEngine) : Scene(e_IGameEngine) {};

	void SetUpScene() override 
	{
		Model* m_NewModel = new Model("assets/meshes/nanosuit.obj");

		Entity e_TestModel;
		Entity e_Player;

		ModelComponent* c_ModelComponent = new ModelComponent;
		c_ModelComponent->m_Model = m_NewModel;

		TransformComponent* c_TransformComponent = new TransformComponent;
		c_TransformComponent->v3_Position = glm::vec3(0.0f, -8.0f, -25.0f);
		c_TransformComponent->q_Orientation = glm::quat(0.0f, 0.0f, 0.0f, 0.0f);
		c_TransformComponent->v3_Scale = glm::vec3(1.0f, 1.0f, 1.0f);

		e_TestModel.AddComponent(c_ModelComponent);
		e_TestModel.AddComponent(c_TransformComponent);

		CameraComponent* c_CameraComponent = new CameraComponent;

		TransformComponent* c_TransformComponent2 = new TransformComponent;
		c_TransformComponent2->v3_Position = glm::vec3(0.0f, 0.0f, 4.0f);
		c_TransformComponent2->q_Orientation = glm::quat(0.0f, 0.0f, 0.0f, 0.0f);
		c_TransformComponent2->v3_Scale = glm::vec3(1.0f, 1.0f, 1.0f);

		e_Player.AddComponent(c_CameraComponent);
		e_Player.AddComponent(c_TransformComponent2);

		vt_EntityList.push_back(e_TestModel);
		vt_EntityList.push_back(e_Player);
		SetCurrentCamera(c_CameraComponent);
	};
};