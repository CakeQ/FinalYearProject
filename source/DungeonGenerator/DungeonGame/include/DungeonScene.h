#pragma once

#include <ImGUI/imgui.h>
#include <ImGUI/imgui_impl_glfw_gl3.h>

#include "Scene.h"
#include "Dungeon.h"
#include "DungeonComponent.h"

class DungeonScene : public Scene
{
public:
	Dungeon* d_CurrentDungeon;
	int i_DungeonSeed;

	DungeonScene(EngineCore* e_IEngine) : Scene(e_IEngine)
	{
		mm_ModelManager->JSONLoadModels("Assets/AssetList.json");
	}

	void SetUpScene() override
	{
		e_PlayerEntity = new PlayerEntity;
		e_PlayerEntity->GetComponent<TransformComponent>()->v3_Position = glm::vec3(0.0f, 0.0f, 2500.0f);
		e_PlayerEntity->GetComponent<CameraComponent>()->q_Orientation = glm::quat(0.0f, 0.0f, 0.0f, 0.0f);

		vt_EntityList.push_back(e_PlayerEntity);
		SetCurrentCamera(e_PlayerEntity->GetComponent<CameraComponent>());

		b2Vec2 b2_Gravity(0.0f, 0.0f);
		b2_World = new b2World(b2_Gravity);
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
		std::vector<Model*> vt_DrawnModels;

		for (Entity* e_IteratorEntity : vt_EntityList)
		{
			if (!e_IteratorEntity->GetComponent<ModelComponent>()) continue;												//!< Check to see if Entity has ModelComponent.
			ModelComponent* c_IteratorModelComponent = e_IteratorEntity->GetComponent<ModelComponent>();
			if (!c_IteratorModelComponent->m_Model || c_IteratorModelComponent->b_Hidden) continue;							//!< Check to see if ModelComponent has Model.
			Model* c_IteratorModel = c_IteratorModelComponent->m_Model;
			bool b_Iterated = false;
			for (InstancedEntity* e_InstancedEntity : vt_InstancedEntities)
			{
				if (c_IteratorModel == e_InstancedEntity->m_Model)
				{
					b_Iterated = true;
				}
			}
			if (b_Iterated) continue;
			e_GameEngine->DrawModel(c_IteratorModel, e_IteratorEntity->GetComponent<TransformComponent>()->GetModelMatrix());
		}
		for (InstancedEntity* e_InstancedEntity : vt_InstancedEntities)
		{
			Model* c_IteratorModel = e_InstancedEntity->m_Model;
			int i_Instances = e_InstancedEntity->vt_EntityList.size();
			glm::mat4* m4_InstancedMatrices = new glm::mat4[i_Instances];
			for (int i = 0; i < e_InstancedEntity->vt_EntityList.size(); i++)
			{
				m4_InstancedMatrices[i] = e_InstancedEntity->vt_EntityList[i]->GetComponent<TransformComponent>()->GetModelMatrix();
			}
			e_GameEngine->DrawModel(c_IteratorModel, m4_InstancedMatrices);
		}
		//if (std::find(vt_DrawnModels.begin(), vt_DrawnModels.end(), c_IteratorModel) != vt_DrawnModels.end()) continue;	//!< Check to see if Model already drawn.

		//std::vector<glm::mat4> vt_Matrices;

		//for (Texture texture : e_IteratorEntity->GetComponent<ModelComponent>()->m_Model->vt_TexturesLoaded)
		//{
		//	glBindTexture(GL_TEXTURE_2D, texture.ui_ID);
		//}

		//for (Entity* e_OtherEntity : vt_EntityList)
		//{
		//	if (!e_OtherEntity->GetComponent<ModelComponent>()) continue;												//!< Check to see if Other Entity has ModelComponent.
		//	ModelComponent* c_OtherModelComponent = e_OtherEntity->GetComponent<ModelComponent>();
		//	if (!c_OtherModelComponent->m_Model || c_OtherModelComponent->b_Hidden) continue;							//!< Check to see if Other ModelComponent has Model.
		//	Model* c_OtherModel = c_OtherModelComponent->m_Model;
		//	if (c_OtherModel != c_IteratorModel) continue;																//!< Check to see if Other Model matches Model.

		//	vt_Matrices.push_back(e_OtherEntity->GetComponent<TransformComponent>()->GetModelMatrix());
		//}

		//glm::mat4* m4_ModelMatrices;
		//m4_ModelMatrices = new glm::mat4[vt_Matrices.size()];
		//for (unsigned int i = 0; i < vt_Matrices.size(); i++)
		//{
		//	m4_ModelMatrices[i] = vt_Matrices.back();
		//	vt_Matrices.pop_back();
		//}
		/*if (d_CurrentDungeon)
		{
			for (Room* e_IteratorRoom : d_CurrentDungeon->vt_RoomList)
			{
				for (DungeonEntity* e_IteratorEntity : e_IteratorRoom->vt_RoomContents)
				{
					if (e_IteratorEntity->GetComponent<ModelComponent>() != nullptr)
					{
						for (Texture texture : e_IteratorEntity->GetComponent<ModelComponent>()->m_Model->vt_TexturesLoaded)
						{
							glBindTexture(GL_TEXTURE_2D, texture.ui_ID);
						}

						if (!e_IteratorEntity->GetComponent<ModelComponent>()->b_Hidden)
						{
							if (e_IteratorEntity->GetComponent<ModelComponent>()->m_Model)
							{
								e_GameEngine->DrawModel(e_IteratorEntity->GetComponent<ModelComponent>()->m_Model, e_IteratorEntity->GetComponent<TransformComponent>()->GetModelMatrix());
							}
						}
					}
				}
			}
		}*/
	}

	void DrawGUI() override
	{
		ImGui::Begin("Debug Window");

		ImGui::SetWindowPos(ImVec2(0, 0));
		ImGui::SetWindowSize(ImVec2(float(e_GameEngine->i_Width*0.1), float(e_GameEngine->i_Height*0.5)));

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
			}
			d_CurrentDungeon = new Dungeon(i_DungeonSeed, mm_ModelManager, this);
		}

		if (ImGui::Button("Generate Random Dungeon"))
		{
			i_DungeonSeed = int(glfwGetTime());
			d_CurrentDungeon = new Dungeon(i_DungeonSeed, mm_ModelManager, this);
		}

		if (ImGui::Button("Clear Dungeon"))
		{
			if (d_CurrentDungeon)
			{
				d_CurrentDungeon = nullptr;
			}
		}
		/*
		static auto GetRoom = [](void* Vec, int Index, const char** OutText)
		{
			std::vector<Room*>* vt_TempList = static_cast<std::vector<Room*>*>(Vec);

			if (Index < 0 || Index >= vt_TempList->size())
				return false;
			*OutText = vt_TempList->at(Index)->GetName();
			return true;
		};

		static int i_ListBoxIndex = -1;

		if (d_CurrentDungeon)
		{
			ImGui::ListBox("", &i_ListBoxIndex, GetRoom, static_cast<void*>(&d_CurrentDungeon->vt_RoomList), d_CurrentDungeon->vt_RoomList.size(), 15);
		}
		*/
		ImGui::End();
	}
};