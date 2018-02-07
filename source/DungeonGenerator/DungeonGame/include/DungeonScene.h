#pragma once

#include "Scene.h"

class DungeonScene : public Scene
{
public:
	DungeonScene(EngineCore* e_IEngine) : Scene(e_IEngine)
	{
		mm_ModelManager->JSONLoadModels("Assets/AssetList.json");

		/*SceneText* t_ControlText = new SceneText;
		t_ControlText->s_Text = "Movement: W A S D | Camera Options: 1 2 | Mouse to move camera";
		t_ControlText->f_TextSize = 0.5f;
		t_ControlText->v2_ScreenPos = glm::vec2(0.005f, 0.005f);
		t_ControlText->v3_TextColor = glm::vec3(1.0f, 1.0f, 1.0f);
		vt_SceneTextList.push_back(t_ControlText);*/
	}

	void SetUpScene() override
	{
		Entity* e_TestModel = new StaticEntity;
		e_PlayerEntity = new PlayerEntity;

		for (Asset* a_IteratorAsset : mm_ModelManager->vt_AssetList)
		{
			if ("wall_s" == a_IteratorAsset->s_ModelName)
			{
				e_TestModel->GetComponent<ModelComponent>()->m_Model = a_IteratorAsset->m_Model;
				continue;
			}
		}

		e_TestModel->GetComponent<TransformComponent>()->v3_Position = glm::vec3(0.0f, 0.0f, -100.0f);
		e_PlayerEntity->GetComponent<TransformComponent>()->v3_Position = glm::vec3(0.0f, 50.0f, 0.0f);

		vt_EntityList.push_back(e_TestModel);
		vt_EntityList.push_back(e_PlayerEntity);
		SetCurrentCamera(e_PlayerEntity->GetComponent<CameraComponent>());
	}
};