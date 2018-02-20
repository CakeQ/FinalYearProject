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
	glm::vec3 v3_DungeonOrigin;
	int i_Seed;


	Dungeon(int i_ISeed, ModelManager* mm_IModelManager, Scene* s_IScene)
	{
		i_Seed = i_ISeed;
		mm_ModelManager = mm_IModelManager;
		s_ParentScene = s_IScene;

		srand(23);
		GenerateDungeon();
	};

	void GenerateDungeon()
	{
		//int i_Rooms = rand()%5 + 10;
		int i_Rooms = 1;

		std::cout << "Generating " << i_Rooms << " rooms." << std::endl;

		for (int i = 0; i < i_Rooms; i++)
		{
			std::cout << "Room " << i + 1 << " generated." << std::endl;
			//Room* r_NewRoom = new Room(glm::vec3(v2_NewPos, 0.0f), glm::vec2(20, 20), glm::vec3(40.0f, 40.0f, 40.0f), s_ParentScene, mm_ModelManager);
			Room* r_NewRoom = new Room(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(9, 9), glm::vec3(39.25f, 39.25f, 39.25f), s_ParentScene, mm_ModelManager);
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
};