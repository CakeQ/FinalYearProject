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

	virtual bool InitWindow(int width, int height, std::string WindowName) = 0;
	virtual bool RunEngine(Game& game) = 0;
	virtual void Draw() = 0;
};