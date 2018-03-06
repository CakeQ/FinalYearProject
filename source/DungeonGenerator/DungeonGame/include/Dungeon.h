#pragma once

#include <stdlib.h>
#include <vector>

#include <glm\glm.hpp>

#include "Scene.h"
#include "ModelManager.h"
#include "Room.h"

class Dungeon
{
private:
	ModelManager* mm_ModelManager;
	Scene* s_ParentScene;

public:
	std::vector<Room> vt_RoomList;
	glm::vec2 v2_RoomSize;
	glm::vec2 v2_Grid = glm::vec2(39.25f, 39.25f);
	glm::vec3 v3_DungeonOrigin;
	int i_Seed;


	Dungeon(int i_ISeed, ModelManager* mm_IModelManager, Scene* s_IScene)
	{
		i_Seed = i_ISeed;
		mm_ModelManager = mm_IModelManager;
		s_ParentScene = s_IScene;

		srand(i_Seed);
		GenerateDungeon();
	};

	void GenerateDungeon()
	{
		int i_Rooms = rand()%5 + 5;
		//int i_Rooms = 1;

		for (int i = 0; i < i_Rooms; i++)
		{
			glm::vec2 v2_RoomSize = glm::vec2(rand() % 6 + 3, rand() % 6 + 3);
			glm::vec2 v2_RoomPos = SnapToGrid(GetRandomPointInCircle(20.0f));
			Room* r_NewRoom = new Room(glm::vec3(v2_RoomPos, 0.0f), v2_RoomSize, glm::vec3(v2_Grid, 0.0f), s_ParentScene, mm_ModelManager);
		}
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
};