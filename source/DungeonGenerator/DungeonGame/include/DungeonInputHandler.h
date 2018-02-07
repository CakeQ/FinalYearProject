#pragma once

#include <json\json.h>

#include <fstream>
#include <sstream>
#include <iostream>

#include "InputHandler.h"

class MoveForwardCommand : public InputCommand
{
public:
	void Execute(Entity& e_IEntity)
	{
		e_IEntity.Message("MovePlayerForward");
	};
};

class MoveBackwardCommand : public InputCommand
{
public:
	void Execute(Entity& e_IEntity)
	{
		e_IEntity.Message("MovePlayerBackward");
	};
};

class MoveLeftCommand : public InputCommand
{
public:
	void Execute(Entity& e_IEntity)
	{
		e_IEntity.Message("MovePlayerLeft");
	};
};

class MoveRightCommand : public InputCommand
{
public:
	void Execute(Entity& e_IEntity)
	{
		e_IEntity.Message("MovePlayerRight");
	};
};

class ChangeViewCommand : public InputCommand
{
public:
	void Execute(Entity& e_IEntity)
	{
		e_IEntity.Message("SetCamera");
	};
};

class ChangeViewFirstPersonCommand : public InputCommand
{
public:
	void Execute(Entity& e_IEntity)
	{
		e_IEntity.Message("SetCameraFirstPerson");
	};
};

class ChangeViewThirdPersonCommand : public InputCommand
{
public:
	void Execute(Entity& e_IEntity)
	{
		e_IEntity.Message("SetCameraThirdPerson");
	};
};

struct DungeonInputHandler : public InputHandler
{
	DungeonInputHandler(Entity* e_IEntity) : InputHandler(e_IEntity)
	{
		LoadJSONConfig("Assets/Config.json");
	}

	bool DungeonInputHandler::LoadJSONConfig(std::string s_ConfigFile)
	{
		std::fstream JSONData;
		Json::Value JSONRoot;
		Json::Reader JSONReader;

		JSONData.open(s_ConfigFile.c_str());

		if (!JSONReader.parse(JSONData, JSONRoot))
		{
			std::cout << "ERROR: Failed to parse data from:" << s_ConfigFile << JSONReader.getFormattedErrorMessages();
			return false;
		}

		std::cout << "Loading input: " << s_ConfigFile << std::endl;

		const Json::Value Config = JSONRoot["Input"];

		for (unsigned int i = 0; i < Config.size(); i++)
		{
			const std::string CommandType = Config[i]["command"].asString();
			const Json::Value Keys = Config[i]["keys"];

			if (Keys.type() == Json::nullValue)
			{
				std::cout << "ERROR: " << CommandType << " has no keys bound!" << std::endl;
				continue;
			}
			else
			{
				for (unsigned int i = 0; i < Keys.size(); i++)
				{
					if (CommandType == "MoveForwardCommand") m_ControlMapping[Keys[i].asInt()] = new MoveForwardCommand;
					else if (CommandType == "MoveLeftCommand") m_ControlMapping[Keys[i].asInt()] = new MoveLeftCommand;
					else if (CommandType == "MoveBackwardCommand") m_ControlMapping[Keys[i].asInt()] = new MoveBackwardCommand;
					else if (CommandType == "MoveRightCommand") m_ControlMapping[Keys[i].asInt()] = new MoveRightCommand;
					else if (CommandType == "SetCameraCommand") m_ControlMapping[Keys[i].asInt()] = new ChangeViewCommand;
					else if (CommandType == "SetCameraFirstPersonCommand") m_ControlMapping[Keys[i].asInt()] = new ChangeViewFirstPersonCommand;
					else if (CommandType == "SetCameraThirdPersonCommand") m_ControlMapping[Keys[i].asInt()] = new ChangeViewThirdPersonCommand;
					else
					{
						std::cout << "ERROR: " << CommandType << " is and unrecognised command!" << std::endl;
						continue;
					}
				}
			}
		}
		return true;
	}
};