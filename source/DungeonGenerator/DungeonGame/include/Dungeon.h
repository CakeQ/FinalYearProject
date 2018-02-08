#pragma once

#include <stdlib.h>
#include <vector>

#include <glm\glm.hpp>

#include "Room.h"

class Dungeon
{
public:
	std::vector<Room> vt_RoomList;
	glm::vec2 v2_RoomSize;
	glm::vec3 v3_DungeonOrigin;
	int i_Seed;


	Dungeon(int i_ISeed)
	{
		i_Seed = i_ISeed;
		srand(i_Seed);
		GenerateDungeon();
	};

	void GenerateDungeon()
	{
		int i_Rooms = rand()%25;

		for (int i; i > i_Rooms; i++)
		{
			Room* r_NewRoom = new Room(); //Fill with stuff
		}
	};

	glm::vec2 GetRandomPointInCircle(float f_IRadius)
	{
		float f_R = f_IRadius - glm::sqrt(rand() % 2) * f_IRadius;
		
		int i_TwoPi = rand() % 62831;									//< Generate a pseudo random of 2*pi because rand doesn't work with floats
		float f_A = i_TwoPi / (glm::two_pi<float>() * 10000);			//< Divide pseudo random by actual 2*pi to get a similar effect of actually generating a rand of 2*pi.

		float f_X = f_IRadius * glm::cos(f_R) * f_R;
		float f_Y = f_IRadius * glm::sin(f_A) * f_R;

		return glm::vec2(f_X, f_Y);
	}
};