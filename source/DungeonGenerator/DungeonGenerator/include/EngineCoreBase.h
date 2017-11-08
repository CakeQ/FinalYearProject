/**
* \file EngineCoreBase.h
*/

//! Parent engine core class.
/*!
Base engine class to which every engine will inherit from.
Created by Daniel Thompson, P15230940.
*/

#pragma once

class Game;

class EngineCore
{
public:
	virtual ~EngineCore() {};

	virtual bool InitWindow(int IWidth, int IHeight, std::string IWindowName) = 0;
	virtual bool RunEngine(Game& IGame) = 0;
	virtual void Draw(const glm::mat4& IModelMatrix) = 0;
};