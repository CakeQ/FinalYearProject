#pragma once

#include "Scene.h"
#include "DungeonEntity.h"
#include "StaticEntity.h"
#include "WallEntity.h"
#include "FloorEntity.h"
#include "ModelManager.h"
#include "PhysicsComponent.h"
#include "DungeonComponent.h"
#include "Dungeon.h"

class Room : public DungeonEntity
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

	Room(glm::vec3 v3_IPosition, glm::vec2 v2_IRoomSize, glm::vec3 v3_ITileSize, Scene* s_IScene, ModelManager* mm_IModelManager) : DungeonEntity(mm_IModelManager)
	{
		AddComponent(new PhysicsComponent);

		s_ParentScene = s_IScene;

		v2_RoomSize = v2_IRoomSize;
		v3_TileSize = v3_ITileSize;
		v3_Position = v3_IPosition;
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
			for (int i = 0; i < v2_RoomSize.x; i++)
			{
				for (int j = 0; j < v2_RoomSize.y; j++)
				{
					std::string s_WallType;
					DungeonEntity* e_NewTile;

					if ((i == 0 || i == v2_RoomSize.x - 1 || j == 0 || j == v2_RoomSize.y - 1))
					{
						e_NewTile = new WallEntity(mm_ModelManager);
						if (i == 0)
						{
							if (j == 0)
							{
								e_NewTile->ChangeState(6);
							}
							else if (j == v2_RoomSize.y - 1)
							{
								e_NewTile->ChangeState(3);
							}
							else
							{
								e_NewTile->ChangeState(10);
							}
						}
						else if (i == v2_RoomSize.x - 1)
						{
							if (j == 0)
							{
								e_NewTile->ChangeState(12);
							}
							else if (j == v2_RoomSize.y - 1)
							{
								e_NewTile->ChangeState(9);
							}
							else
							{
								e_NewTile->ChangeState(10);
							}
						}
						else
						{
							e_NewTile->ChangeState(5);
						}
					}
					else
					{
						e_NewTile = new FloorEntity(mm_ModelManager);
					}

					DungeonComponent* c_DungeonComponent = new DungeonComponent();
					c_DungeonComponent->i_Seed = GetComponent<DungeonComponent>()->i_Seed;
					e_NewTile->AddComponent(c_DungeonComponent);
					e_NewTile->GetComponent<TransformComponent>()->v3_Position = v3_Position + glm::vec3((v3_TileSize.x * i), (v3_TileSize.y * j), 0);
					vt_RoomContents.push_back(e_NewTile);
					s_ParentScene->vt_EntityList.push_back(e_NewTile);
				}
			}
			b_Generated = true;
			s_ParentScene->SortInstancedEntities();
		}
	}

	void RemoveTile(DungeonEntity* e_ITile)
	{
		for (unsigned int i = 0; i < vt_RoomContents.size(); i++)
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
		c_PhysicsComponent->b2_BodyDef.fixedRotation = true;
		c_PhysicsComponent->b2_Body = s_ParentScene->b2_World->CreateBody(&c_PhysicsComponent->b2_BodyDef);

		c_PhysicsComponent->b2_Shape.SetAsBox((((v3_TileSize.x * (v2_RoomSize.x + 1)) / 2 + 15) / 30), (((v3_TileSize.y * (v2_RoomSize.y + 1)) / 2 + 15) / 30));
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

	const char* GetName()
	{
		return "Room " + i_RoomID;
	}

	void CalculateState() {};
	void ChangeState() {};
};