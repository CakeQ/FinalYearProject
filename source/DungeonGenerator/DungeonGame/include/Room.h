#pragma once

#include "Scene.h"
#include "Entity.h"
#include "StaticEntity.h"
#include "WallEntity.h"
#include "FloorEntity.h"
#include "ModelManager.h"

class Room : public Entity
{
private:
	bool b_Generated = false;	

public:
	std::vector<Entity*> vt_RoomContents;
	glm::vec2 v2_RoomSize;
	glm::vec3 v3_TileSize;
	glm::vec3 v3_Position;

	Scene* s_ParentScene;
	ModelManager* mm_ModelManager;

	Room(glm::vec3 v3_IPosition, glm::vec2 v2_IRoomSize, glm::vec3 v3_ITileSize, Scene* s_IScene, ModelManager* mm_IModelManager)
	{
		AddComponent(new TransformComponent);
		mm_ModelManager = mm_IModelManager;
		s_ParentScene = s_IScene;

		v2_RoomSize = v2_IRoomSize;
		v3_TileSize = v3_ITileSize;
		v3_Position = v3_IPosition;

		GenerateRoom(mm_IModelManager);
	};

	void GenerateRoom(ModelManager* mm_IModelManager)
	{

		for (int i_Layer = 0; i_Layer < 2; i_Layer++)
		{
			for (int i = 0; i < v2_RoomSize.x; i++)
			{
				for (int j = 0; j < v2_RoomSize.y; j++)
				{
					std::string s_WallType;
					int i_WallRotation;
					StaticEntity* e_NewTile;

					if ((i_Layer == 1) && (i == 0 || i == v2_RoomSize.x - 1 || j == 0 || j == v2_RoomSize.y - 1))
					{
						/*if ((i == 0 && j == 0) || (i == 0 && j == v2_RoomSize.y - 1) || (i == v2_RoomSize.x - 1 && j == 0) || (i == v2_RoomSize.x - 1 && j == v2_RoomSize.y - 1))
						{
							s_WallType = "wall_c";
						}
						else
						{
							s_WallType = "wall_s";
						}*/
						e_NewTile = new WallEntity(mm_IModelManager);
					}
					else if (i_Layer == 0)
					{
						//s_WallType = "floor_s";
						e_NewTile = new FloorEntity(mm_IModelManager);
					}
					else
					{
						continue;
					}

					/*for (Asset* a_IteratorAsset : mm_IModelManager->vt_AssetList)
					{
						if (s_WallType == a_IteratorAsset->s_ModelName)
						{
							e_NewTile->GetComponent<ModelComponent>()->m_Model = a_IteratorAsset->m_Model;
							continue;
						}
					}*/
					e_NewTile->GetComponent<TransformComponent>()->v3_Position = v3_Position + glm::vec3((v3_TileSize.x * i), (v3_TileSize.y * j), (3.95f * i_Layer));
					s_ParentScene->vt_EntityList.push_back(e_NewTile);
				}
			}
		}
	};

	void Update(float f_IDeltaTime) override {};
	void Message(const std::string s_IMessage) override {};
};