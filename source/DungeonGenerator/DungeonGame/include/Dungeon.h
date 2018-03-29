#pragma once

#include <stdlib.h>
#include <vector>

#include <glm\glm.hpp>

#include "Scene.h"
#include "ModelManager.h"
#include "DungeonEntity.h"
#include "Room.h"

class Dungeon
{
private:
	ModelManager* mm_ModelManager;
	Scene* s_ParentScene;

public:
	std::vector<Room*> vt_RoomList;
	std::vector<DungeonEntity*> vt_Tiles;
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
			e_IteratorRoom->~Room();
		}
	}

	void SpawnDungeon()
	{
		int i_Rooms = rand()%5 + 5;
		//int i_Rooms = 1;

		for (int i = 0; i < i_Rooms; i++)
		{
			glm::vec2 v2_RoomSize = glm::vec2(rand() % 6 + 3, rand() % 6 + 3);
			/*if ((int(v2_RoomSize.x) % 2) == 0)
			{
				v2_RoomSize.x += 1;
			}
			if ((int(v2_RoomSize.y) % 2) == 0)
			{
				v2_RoomSize.y += 1;
			}*/
			glm::vec2 v2_RoomPos = SnapToGrid(GetRandomPointInCircle(5.0f));
			SpawnRoom(glm::vec3(v2_RoomPos, 0.0f), v2_RoomSize, i);
		}

		for (Room* e_IteratorRoom : vt_RoomList)
		{
			e_IteratorRoom->AddPhysics();
		}

		b_Spreading = true;
	};

	glm::vec2 GetRandomPointInCircle(float f_IRadius)
	{
		float f_R = f_IRadius - glm::sqrt(rand() % 2) * f_IRadius;

		int i_TwoPi = rand() % 62831;									//< Generate a pseudo random of 2*pi because rand doesn't work with floats.
		float f_A = i_TwoPi / 10000.0f;									//< Divide pseudo random by 10000 to achieve actual floated pseudo pi.

		float f_X = f_IRadius * glm::cos(f_R) * f_R;
		float f_Y = f_IRadius * glm::sin(f_A) * f_R;

		return glm::vec2(f_X, f_Y);
	}

	glm::vec2 SnapToGrid(glm::vec2 v2_IPos)
	{
		glm::vec2 v2_SnappedPos = glm::vec2(floor(v2_IPos.x / v2_Grid.x + 0.5) * v2_Grid.x, floor(v2_IPos.y / v2_Grid.y + 0.5) * v2_Grid.y);
		return v2_SnappedPos;
	}

	void SpawnRoom(glm::vec3 v3_IRoomPos, glm::vec2 v2_IRoomSize, int i_IID)
	{
		Room* r_NewRoom = new Room(v3_IRoomPos, v2_IRoomSize, glm::vec3(v2_Grid, 0.0f), s_ParentScene, mm_ModelManager);
		r_NewRoom->i_RoomID = i_IID;
		vt_RoomList.push_back(r_NewRoom);
	}

	void InitialiseTiles()
	{

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
			InitialiseTiles();
			b_Initialised = true;
			std::cout << "No longer spreading" << std::endl;
			for (Room* e_IteratorRoom : vt_RoomList)
			{
				e_IteratorRoom->b_Moving = false;
				e_IteratorRoom->RemovePhysics();
				for (DungeonEntity* e_IteratorEntity : e_IteratorRoom->vt_RoomContents)
				{
					vt_Tiles.push_back(e_IteratorEntity);
				}
			}

			for (DungeonEntity* e_IteratorEntity : vt_Tiles)
			{
				e_IteratorEntity->ChangeState();
			}
		}
	}
};