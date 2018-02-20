#pragma once

#include "Scene.h"
#include "Entity.h"
#include "StaticEntity.h"
#include "ModelManager.h"

class Room : public Entity
{
private:
	bool b_Generated = false;	

public:
	std::vector<Entity*> vt_RoomContents;
	glm::vec2 v2_RoomSize;
	glm::vec3 v3_TileSize;
	glm::vec3 v3_TileOffset;

	Scene* s_ParentScene;
	ModelManager* mm_ModelManager;

	Room(glm::vec3 v3_IPosition, glm::vec2 v2_IRoomSize, glm::vec3 v3_ITileSize, Scene* s_IScene, ModelManager* mm_IModelManager)
	{
		AddComponent(new TransformComponent);
		mm_ModelManager = mm_IModelManager;
		s_ParentScene = s_IScene;

		v2_RoomSize = v2_IRoomSize;
		v3_TileSize = v3_ITileSize;
		v3_TileOffset = v3_IPosition - glm::vec3(((v2_IRoomSize.x * v3_TileSize.x)/2.0f), ((v2_IRoomSize.y * v3_TileSize.y)/2.0f), 0.0f);

		GenerateRoom(mm_IModelManager);
	};

	void GenerateRoom(ModelManager* mm_IModelManager)
	{
		std::cout << "Room position: " << v3_TileOffset.x << "," << v3_TileOffset.y << std::endl;

		for (int i_Layer = 0; i_Layer < 2; i_Layer++)
		{
			for (int i = 0; i < v2_RoomSize.x; i++)
			{
				for (int j = 0; j < v2_RoomSize.y; j++)
				{
					std::cout << i_Layer;

					std::string s_WallType;
					int i_WallRotation;

					if ((i_Layer == 1) && (i == 0 || i == v2_RoomSize.x - 1 || j == 0 || j == v2_RoomSize.y - 1))
					{
						s_WallType = "wall_s";
					}
					else if (i_Layer == 0)
					{
						s_WallType = "floor_s";
					}
					else
					{
						continue;
					}

					StaticEntity* e_NewWall = new StaticEntity;

					for (Asset* a_IteratorAsset : mm_IModelManager->vt_AssetList)
					{
						if (s_WallType == a_IteratorAsset->s_ModelName)
						{
							e_NewWall->GetComponent<ModelComponent>()->m_Model = a_IteratorAsset->m_Model;
							continue;
						}
					}

					std::cout << "Spawning " << s_WallType << std::endl;
					e_NewWall->GetComponent<TransformComponent>()->v3_Position = v3_TileOffset + glm::vec3((v3_TileSize.x * i), (v3_TileSize.y * j), (3.95f * i_Layer));
					s_ParentScene->vt_EntityList.push_back(e_NewWall);
				}
			}
		}
	};

	void Update(float f_IDeltaTime) override {};
	void Message(const std::string s_IMessage) override {};
};