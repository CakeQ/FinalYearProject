/**
* \file Input.h
*/

//! Input controller class.
/*!
Handler for all input recieved in game.
Created by Daniel Thompson, P15230940.
*/

#pragma once

#include <map>
#include <vector>
#include <Entity.h>

class InputCommand
{
public:
	virtual ~InputCommand() {};
	virtual void Execute() = 0;
};

class TestCommand : public InputCommand
{
public:
	void Execute() {};
};

struct InputHandler
{

	std::map<int, InputCommand*> ControlMapping;

	InputHandler()
	{
		ControlMapping[65] = new TestCommand; // A key
	}

	void HandleInputs(const std::vector<bool>& KeyBuffer)
	{
		for (const auto& MapEntry : ControlMapping)
		{
			if (KeyBuffer[MapEntry.first])
			{
				MapEntry.second->Execute();
			}
		}
	}
};