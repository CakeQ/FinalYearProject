#pragma once

#include <stdlib.h>
#include <vector>

#include <glm\glm.hpp>

#include "Room.h"

class Dungeon
{
public:
	std::vector<Room> vt_RoomList;

	Dungeon(int i_ISeed)
	{
		srand(i_ISeed);
		GenerateDungeon();
	};

	void GenerateDungeon()
	{
		int i_Rooms = rand()%25;

		for (int i; i > i_Rooms; i++)
		{
			Room* r_NewRoom = new Room;

		}
	};

	glm::vec2 GetRandomPointInCircle(float f_IRadius)
	{
		
		/*float t = 2 * glm::pi() * rand();
		float u = math.random() + math.random();
		float r;
		if (u > 1)
		{
			r = 2 - u;
		}
		else
		{
			r = u;
		}
		return radius*r*math.cos(t), radius*r*math.sin(t);*/ //WORK IN PROGRESS
	}
};