/**
* \file EngineCoreGLFW.h
*/

//! GLFW engine core class.
/*!
GLFW engine class to which will be used if GLFW is enabled.
Created by Daniel Thompson, P15230940.
*/

#pragma once

#include <EngineCoreBase.h>
#include <vector>

#include <Shader.h>

class Game;

class EngineCoreGLFW : public EngineCore
{
private:
	GLFWwindow* WindowID;
	static std::vector<bool> KeyBuffer;
	static const int KeyBufferSize = 400;

	Shader ShaderProgram;

	int NumberOfTriangles = 4;

	static void MouseMoveCallbackEvent(GLFWwindow* IWindow, double IXPos, double IYPos) {};
	static void KeyCallbackEvent(GLFWwindow* IWindow, int IKey, int IScanCode, int IAction, int IMods);
	static void WindowResizeCallbackEvent(GLFWwindow* IWindow, int IWidth, int IHeight);

public:
	EngineCoreGLFW();
	~EngineCoreGLFW() override;

	bool InitWindow(int IWidth, int IHeight, std::string IWindowName) override;
	bool RunEngine(Game& IGameID) override;
	void Draw(const glm::mat4& IModelMatrix);
};

