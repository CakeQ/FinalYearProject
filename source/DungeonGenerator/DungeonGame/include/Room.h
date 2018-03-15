#pragma once

#include "Scene.h"
#include "Entity.h"
#include "StaticEntity.h"
#include "WallEntity.h"
#include "FloorEntity.h"
#include "ModelManager.h"
#include "PhysicsComponent.h"

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
		AddComponent(new PhysicsComponent);

		mm_ModelManager = mm_IModelManager;
		s_ParentScene = s_IScene;

		v2_RoomSize = v2_IRoomSize;
		v3_TileSize = v3_ITileSize;
		v3_Position = v3_IPosition;

		GenerateRoom();
	}

	void GenerateRoom()
	{
		if (!b_Generated)
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
							e_NewTile = new WallEntity(mm_ModelManager);
						}
						else if (i_Layer == 0)
						{
							//s_WallType = "floor_s";
							e_NewTile = new FloorEntity(mm_ModelManager);
						}
						else
						{
							continue;
						}

						/*for (Asset* a_IteratorAsset : mm_ModelManager->vt_AssetList)
						{
							if (s_WallType == a_IteratorAsset->s_ModelName)
							{
								e_NewTile->GetComponent<ModelComponent>()->m_Model = a_IteratorAsset->m_Model;
								continue;
							}
						}*/
						e_NewTile->GetComponent<TransformComponent>()->v3_Position = v3_Position + glm::vec3((v3_TileSize.x * i), (v3_TileSize.y * j), (3.95f * i_Layer));
						e_NewTile->GetComponent<TransformComponent>()->q_Orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
						vt_RoomContents.push_back(e_NewTile);
						s_ParentScene->vt_EntityList.push_back(e_NewTile);
					}
				}
			}
			b_Generated = true;
		}
	}

	void AddPhysics()
	{
		PhysicsComponent* c_PhysicsComponent = GetComponent<PhysicsComponent>();
		c_PhysicsComponent->b2_BodyDef.position = b2Vec2(v3_Position.x, v3_Position.y);
		c_PhysicsComponent->b2_BodyDef.type = b2_dynamicBody;
		c_PhysicsComponent->b2_Body = s_ParentScene->b2_World->CreateBody(&c_PhysicsComponent->b2_BodyDef);

		c_PhysicsComponent->b2_Shape.SetAsBox(((v3_TileSize.x * v2_RoomSize.x) / 2), ((v3_TileSize.y * v2_RoomSize.y) / 2));
		c_PhysicsComponent->b2_FixtureDef.density = 1.0f;
		c_PhysicsComponent->b2_FixtureDef.friction = 0.7f;
		c_PhysicsComponent->b2_FixtureDef.shape = &c_PhysicsComponent->b2_Shape;
		c_PhysicsComponent->b2_FixtureDef.restitution = 1.0f;

		c_PhysicsComponent->b2_Body->CreateFixture(&c_PhysicsComponent->b2_FixtureDef);
	}

	void RemovePhysics()
	{

	}

	glm::vec2 SnapToGrid(glm::vec2 v2_IPos)
	{
		glm::vec2 v2_SnappedPos = glm::vec2(floor(v2_IPos.x / v3_TileSize.x + 0.5) * v3_TileSize.x, floor(v2_IPos.y / v3_TileSize.y + 0.5) * v3_TileSize.y);
		return v2_SnappedPos;   
	}

	void Update(float f_IDeltaTime) override 
	{
		glm::vec2 v2_NewPos = SnapToGrid(glm::vec2(GetComponent<PhysicsComponent>()->b2_Body->GetPosition().x - GetComponent<TransformComponent>()->v3_Position.x, GetComponent<PhysicsComponent>()->b2_Body->GetPosition().y - GetComponent<TransformComponent>()->v3_Position.y));
		//glm::vec2 v2_NewPos = glm::vec2(b2_Body->GetPosition().x - GetComponent<TransformComponent>()->v3_Position.x, b2_Body->GetPosition().y - GetComponent<TransformComponent>()->v3_Position.y);
		GetComponent<TransformComponent>()->v3_Position += glm::vec3(v2_NewPos, 0.0f);
		for (Entity* e_IteratorEntity : vt_RoomContents)
		{
			e_IteratorEntity->GetComponent<TransformComponent>()->v3_Position += glm::vec3(v2_NewPos, 0.0f);
		}
	}

	void Message(const std::string s_IMessage) override {}
};