#pragma once

#include "Scene.h"
#include "Dungeon.h"

class DungeonScene : public Scene
{
public:
	Dungeon* d_CurrentDungeon;

	DungeonScene(EngineCore* e_IEngine) : Scene(e_IEngine)
	{
		mm_ModelManager->JSONLoadModels("Assets/AssetList.json");
	}

	void SetUpScene() override
	{
		e_PlayerEntity = new PlayerEntity;
		e_PlayerEntity->GetComponent<TransformComponent>()->v3_Position = glm::vec3(-225.0f, -225.0f, 500.0f);
		e_PlayerEntity->GetComponent<CameraComponent>()->q_Orientation = glm::quat(0.0f, 0.0f, 0.0f, 0.0f);

		vt_EntityList.push_back(e_PlayerEntity);
		SetCurrentCamera(e_PlayerEntity->GetComponent<CameraComponent>());

		int i_TestSeed = rand();
		d_CurrentDungeon = new Dungeon(i_TestSeed, mm_ModelManager, this);
	}
};