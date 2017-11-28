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
	GLFWwindow* w_WindowID;
	static std::vector<bool> vt_KeyBuffer;
	static const int i_KeyBufferSize = 400;

	Shader* s_ShaderProgram;

	static void MouseMoveCallbackEvent(GLFWwindow* w_IWindow, double d_IXPos, double d_IYPos) {};
	static void KeyCallbackEvent(GLFWwindow* w_IWindow, int i_IKey, int i_IScanCode, int i_IAction, int i_IMods);
	static void WindowResizeCallbackEvent(GLFWwindow* i_IWindow, int i_IWidth, int i_IHeight);

public:
	EngineCoreGLFW();
	~EngineCoreGLFW() override;

	bool InitWindow(int i_IWidth, int i_IHeight, std::string i_IWindowName) override;
	bool RunEngine(Game& g_IGameID) override;
	void Draw(const glm::mat4& m4_IModelMatrix);
};

