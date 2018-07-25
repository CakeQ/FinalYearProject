#pragma once

#include <stdlib.h>
#include <vector>

#include <glm\glm.hpp>

#include "Scene.h"
#include "ModelManager.h"
#include "DungeonComponent.h"
#include "Room.h"

class Dungeon
{
private:
	ModelManager* mm_ModelManager;
	Scene* s_ParentScene;

public:
	std::vector<Room*> vt_RoomList;
	glm::vec2 v2_RoomSize;
	glm::vec2 v2_Grid = glm::vec2(39.25f, 39.25f);
	glm::vec3 v3_DungeonOrigin;
	bool b_Spreading = false;
	bool b_Initialised = false;
	int i_Seed;


	Dungeon(int i_ISeed, ModelManager* mm_IModelManager, Scene* s_IScene)
	{
		i_Seed = i_ISeed;
		mm_ModelManager = mm_IModelManager;
		s_ParentScene = s_IScene;

		srand(i_Seed);
		SpawnDungeon();
	};

	~Dungeon()
	{
		for (Room* e_IteratorRoom : vt_RoomList)
		{
			vt_RoomList.pop_back();
		}
		for (unsigned int i = s_ParentScene->vt_EntityList.size(); i < 0; i--)
		{
			Entity* e_IteratorEntity = s_ParentScene->vt_EntityList[i];
			if (e_IteratorEntity->GetComponent<DungeonComponent>())
			{
				DungeonComponent* c_DungeonComponent = e_IteratorEntity->GetComponent<DungeonComponent>();
				if (c_DungeonComponent->i_Seed == i_Seed)
				{
					s_ParentScene->vt_EntityList.erase(s_ParentScene->vt_EntityList.begin() + i);
				}
			}
		}
		for (unsigned int i = s_ParentScene->vt_InstancedEntities.size(); i < 0; i--)
		{
			InstancedEntity* e_IteratorInstance = s_ParentScene->vt_InstancedEntities[i];
			for (unsigned int i = e_IteratorInstance->vt_EntityList.size(); i < 0; i--)
			{
				Entity* e_IteratorEntity = e_IteratorInstance->vt_EntityList[i];
				if (e_IteratorEntity->GetComponent<DungeonComponent>())
				{
					DungeonComponent* c_DungeonComponent = e_IteratorEntity->GetComponent<DungeonComponent>();
					if (c_DungeonComponent->i_Seed == i_Seed)
					{
						e_IteratorInstance->vt_EntityList.erase(s_ParentScene->vt_EntityList.begin() + i);
					}
				}
			}
		}
	}

	void SpawnDungeon()
	{
		int i_Rooms = rand()%5 + 10;

		for (int i = 0; i < i_Rooms; i++)
		{
			glm::vec2 v2_RoomSize = glm::vec2(rand() % 6 + 5, rand() % 6 + 5);
			if ((int(v2_RoomSize.x) % 2) == 0)
			{
				v2_RoomSize.x += 1;
			}
			if ((int(v2_RoomSize.y) % 2) == 0)
			{
				v2_RoomSize.y += 1;
			}
			glm::vec2 v2_RoomPos = GetRandomPointInCircle(10.0f);
			SpawnRoom(glm::vec3(v2_RoomPos, 0.0f), v2_RoomSize, i);
			i_Seed++;
			srand(i_Seed);
		}

		for (Room* e_IteratorRoom : vt_RoomList)
		{
			e_IteratorRoom->AddPhysics();
		}

		b_Spreading = true;
	};

	glm::vec2 GetRandomPointInCircle(float f_IRadius)
	{
		double f_R = f_IRadius - glm::sqrt(double(rand() % 100) / 100) * f_IRadius;

		int i_TwoPi = rand() % 62831;									//< Generate a pseudo random of 2*pi because rand doesn't work with floats.
		float f_A = i_TwoPi / 10000.0f;									//< Divide pseudo random by 10000 to achieve actual floated pseudo pi.

		float f_X = f_IRadius * glm::cos(f_A) * float(f_R);
		float f_Y = f_IRadius * glm::sin(f_A) * float(f_R);

		return glm::vec2(f_X, f_Y);
	}

	glm::vec2 SnapToGrid(glm::vec2 v2_IPos)
	{
		glm::vec2 v2_SnappedPos = glm::vec2(floor(v2_IPos.x / v2_Grid.x + 0.5) * v2_Grid.x, floor(v2_IPos.y / v2_Grid.y + 0.5) * v2_Grid.y);
		return v2_SnappedPos;
	}

	void SpawnRoom(glm::vec3 v3_IRoomPos, glm::vec2 v2_IRoomSize, int i_IID)
	{
		std::cout << "Room spawned at " << v3_IRoomPos.x << ", " << v3_IRoomPos.y << std::endl;
		Room* r_NewRoom = new Room(v3_IRoomPos, v2_IRoomSize, glm::vec3(v2_Grid, 0.0f), s_ParentScene, mm_ModelManager);
		DungeonComponent* c_NewDungeonComponent = new DungeonComponent();
		c_NewDungeonComponent->i_Seed = i_Seed;
		r_NewRoom->AddComponent(c_NewDungeonComponent);
		r_NewRoom->i_RoomID = i_IID;
		r_NewRoom->GenerateRoom();
		vt_RoomList.push_back(r_NewRoom);
		s_ParentScene->vt_EntityList.push_back(r_NewRoom);
	}

	void Update(float f_IDeltaTime)
	{
		b_Spreading = false;
		for (Room* e_IteratorRoom : vt_RoomList)
		{
			e_IteratorRoom->Update(f_IDeltaTime);
			if (e_IteratorRoom->GetComponent<PhysicsComponent>())
			{
				if (e_IteratorRoom->GetComponent<PhysicsComponent>()->b2_Body->IsAwake())
				{
					b_Spreading = true;
				}
			}
		}
		if (b_Spreading == false && b_Initialised == false)
		{
			for (Room* e_IteratorRoom : vt_RoomList)
			{
				e_IteratorRoom->b_Moving = false;
				e_IteratorRoom->RemovePhysics();
			}

			b_Initialised = true;
		}
	}
};