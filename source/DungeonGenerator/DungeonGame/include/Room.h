#pragma once

#include "Scene.h"
#include "DungeonEntity.h"
#include "StaticEntity.h"
#include "WallEntity.h"
#include "FloorEntity.h"
#include "ModelManager.h"
#include "PhysicsComponent.h"

class Room : public Entity
{
public:
	bool b_Generated = false;
	bool b_Moving = true;

	int i_RoomID = 0;

	std::vector<DungeonEntity*> vt_RoomContents;
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

	~Room()
	{
		for (DungeonEntity* e_IteratorEntity : vt_RoomContents)
		{
			vt_RoomContents.pop_back();
		}
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
						DungeonEntity* e_NewTile;

						if ((i_Layer == 1) && (i == 0 || i == v2_RoomSize.x - 1 || j == 0 || j == v2_RoomSize.y - 1))
						{
							e_NewTile = new WallEntity(mm_ModelManager);
						}
						else if (i_Layer == 0)
						{
							e_NewTile = new FloorEntity(mm_ModelManager);
						}
						else
						{
							continue;
						}

						e_NewTile->GetComponent<TransformComponent>()->v3_Position = v3_Position + glm::vec3((v3_TileSize.x * i), (v3_TileSize.y * j), (3.95f * i_Layer));
						e_NewTile->GetComponent<TransformComponent>()->q_Orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
						vt_RoomContents.push_back(e_NewTile);
					}
				}
			}
			b_Generated = true;
		}
	}

	void RemoveTile(DungeonEntity* e_ITile)
	{
		for (int i = 0; i < vt_RoomContents.size(); i++)
		{
			if (e_ITile == vt_RoomContents[i])
			{
				vt_RoomContents.erase(vt_RoomContents.begin() + i);
				delete e_ITile;
			}
		}
	}

	void AddPhysics()
	{
		PhysicsComponent* c_PhysicsComponent = GetComponent<PhysicsComponent>();
		c_PhysicsComponent->b2_BodyDef.position = b2Vec2(v3_Position.x / 30, v3_Position.y / 30);
		c_PhysicsComponent->b2_BodyDef.type = b2_dynamicBody;
		c_PhysicsComponent->b2_Body = s_ParentScene->b2_World->CreateBody(&c_PhysicsComponent->b2_BodyDef);

		c_PhysicsComponent->b2_Shape.SetAsBox((((v3_TileSize.x * v2_RoomSize.x) / 2 + 15) / 30), (((v3_TileSize.y * v2_RoomSize.y) / 2 + 15) / 30));
		c_PhysicsComponent->b2_FixtureDef.density = 1.0f;
		c_PhysicsComponent->b2_FixtureDef.friction = 0.7f;
		c_PhysicsComponent->b2_FixtureDef.shape = &c_PhysicsComponent->b2_Shape;
		c_PhysicsComponent->b2_FixtureDef.restitution = 1.0f;

		c_PhysicsComponent->b2_Body->CreateFixture(&c_PhysicsComponent->b2_FixtureDef);
	}

	void RemovePhysics()
	{
		if (GetComponent<PhysicsComponent>()->b2_Body)
		{
			s_ParentScene->b2_World->DestroyBody(GetComponent<PhysicsComponent>()->b2_Body);
		}
	}

	glm::vec2 SnapToGrid(glm::vec2 v2_IPos)
	{
		glm::vec2 v2_SnappedPos = glm::vec2(floor(v2_IPos.x / v3_TileSize.x + 0.5) * v3_TileSize.x, floor(v2_IPos.y / v3_TileSize.y + 0.5) * v3_TileSize.y);
		return v2_SnappedPos;   
	}

	void Update(float f_IDeltaTime) override
	{
		if (b_Moving)
		{
			glm::vec2 v2_NewPos = SnapToGrid(glm::vec2((GetComponent<PhysicsComponent>()->b2_Body->GetPosition().x * 30) - GetComponent<TransformComponent>()->v3_Position.x, (GetComponent<PhysicsComponent>()->b2_Body->GetPosition().y * 30) - GetComponent<TransformComponent>()->v3_Position.y));
			GetComponent<TransformComponent>()->v3_Position += glm::vec3(v2_NewPos, 0.0f);
			for (DungeonEntity* e_IteratorEntity : vt_RoomContents)
			{
				e_IteratorEntity->GetComponent<TransformComponent>()->v3_Position += glm::vec3(v2_NewPos, 0.0f);
			}
		}
	}

	void Message(const std::string s_IMessage) override {}
};