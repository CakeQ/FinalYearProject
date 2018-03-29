#pragma once

#include <ImGUI/imgui.h>
#include <ImGUI/imgui_impl_glfw_gl3.h>

#include "Scene.h"
#include "Dungeon.h"

#include "DebugDraw.h"

class DungeonScene : public Scene
{
public:
	Dungeon* d_CurrentDungeon;
	DebugDraw* d_DebugDraw;

	bool b_Debug = true;
	int i_DungeonSeed;

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

		b2Vec2 b2_Gravity(0.0f, 0.0f);
		b2_World = new b2World(b2_Gravity);

		//int i_TestSeed = glfwGetTime();
		int i_TestSeed = 413;
		//d_CurrentDungeon = new Dungeon(i_TestSeed, mm_ModelManager, this);

		if (b_Debug == true)
		{
			d_DebugDraw = new DebugDraw;
			b2_World->SetDebugDraw(d_DebugDraw);
			d_DebugDraw->SetFlags(b2Draw::e_shapeBit);
		}
	}

	void Update(float f_IDeltaTime) override
	{
		for (Entity* o_Iterator : vt_EntityList)
		{
			o_Iterator->Update(f_IDeltaTime);
		}

		if (b2_World)
		{
			b2_World->Step(f_IDeltaTime, 8, 3);
		} 
		if (d_CurrentDungeon)
		{
			d_CurrentDungeon->Update(f_IDeltaTime);
		}
	}

	void Draw() override
	{
		float f_RedValue = 0, f_GreenValue = 0, f_BlueValue = 0;
		e_GameEngine->RenderColouredBackground(f_RedValue, f_GreenValue, f_BlueValue);
		e_GameEngine->SetCamera(c_SceneCamera);

		for (Entity* e_EntityIterator : vt_EntityList)
		{
			if (e_EntityIterator->GetComponent<ModelComponent>() != nullptr)
			{
				for (Texture texture : e_EntityIterator->GetComponent<ModelComponent>()->m_Model->vt_TexturesLoaded)
				{
					glBindTexture(GL_TEXTURE_2D, texture.ui_ID);
				}

				if (!e_EntityIterator->GetComponent<ModelComponent>()->b_Hidden)
				{
					if (e_EntityIterator->GetComponent<ModelComponent>()->m_Model)
					{
						e_GameEngine->DrawModel(e_EntityIterator->GetComponent<ModelComponent>()->m_Model, e_EntityIterator->GetComponent<TransformComponent>()->GetModelMatrix());
					}
				}
			}
		}

		if (b_Debug)
		{
			for (Room* e_IteratorRoom : d_CurrentDungeon->vt_RoomList)
			{
				if (e_IteratorRoom->GetComponent<PhysicsComponent>())
				{
					e_GameEngine->DrawDebug(e_IteratorRoom->GetComponent<PhysicsComponent>(), e_IteratorRoom->GetComponent<TransformComponent>()->GetModelMatrix());
				}
			}
		}
		
		/*for (SceneText* t_Iterator : vt_SceneTextList)
		{
		e_EngineCore->RenderText(t_Iterator->s_Text, t_Iterator->v2_ScreenPos.x, t_Iterator->v2_ScreenPos.y, t_Iterator->f_TextSize, t_Iterator->v3_TextColor);
		}*/
	}

	void DrawGUI() override
	{
		ImGui::Begin("Debug Window");

		ImGui::SetWindowPos(ImVec2(0, 0));
		ImGui::SetWindowSize(ImVec2(e_GameEngine->i_Width*0.1, e_GameEngine->i_Height*0.5));

		ImGui::InputInt("Seed", &i_DungeonSeed);

		if (ImGui::Button("Generate Seeded Dungeon"))
		{	
			if (d_CurrentDungeon)
			{
				for (Room* e_IteratorRoom : d_CurrentDungeon->vt_RoomList)
				{
					if (d_CurrentDungeon->b_Spreading)
					{
						e_IteratorRoom->RemovePhysics();
					}
				}

				d_CurrentDungeon->~Dungeon();		
			}
			d_CurrentDungeon = new Dungeon(i_DungeonSeed, mm_ModelManager, this);
		}

		if (ImGui::Button("Generate Random Dungeon"))
		{
			if (d_CurrentDungeon)
			{
				d_CurrentDungeon->~Dungeon();
			}
			i_DungeonSeed = glfwGetTime();
			d_CurrentDungeon = new Dungeon(i_DungeonSeed, mm_ModelManager, this);
		}

		ImGui::End();
	}
};