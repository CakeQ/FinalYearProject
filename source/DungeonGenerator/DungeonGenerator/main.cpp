/**
* \file main.cpp
*/

//! Main game loop.
/*!
Main code file that contains the program's loop used to run everything else.
Created by Daniel Thompson, P15230940.
*/

#define USE_GLFW 1

#ifdef USE_GLFW
#include <EngineCoreBase.h>
#include <EngineCoreGLFW.h>
#endif

#include <Game.h>

int main(int argc, char* argv[])
{
	EngineCore* EngineController;

#ifdef USE_GLFW
	EngineController = new EngineCoreGLFW;
#endif

	if (!EngineController->InitWindow(800, 600, "Window"))
		return 1;

	Game GameController;

	EngineController->RunEngine(GameController);

	return 0;																										//!< Exit program.
}