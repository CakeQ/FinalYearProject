/**
* \file main.cpp
*/

//! Main game loop.
/*!
Main code file that contains the program's loop used to run everything else.
Created by Daniel Thompson, P15230940.
*/
#include <stdafx.h>

#include <Game.h>

int _tmain(int argc, _TCHAR* argv[])
{
	EngineCore* EngineController;

#ifdef USE_GLFW
	EngineController = new EngineCoreGLFW;
#endif

	if (!EngineController->InitWindow(800, 600, "Window"))
		return 1;

	Game GameController(EngineController);

	EngineController->RunEngine(GameController);

	return 0;																										//!< Exit program.
}