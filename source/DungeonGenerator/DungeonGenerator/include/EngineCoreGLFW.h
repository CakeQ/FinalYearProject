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
#include <glfw3.h>
#include <vector>

class Game;

class EngineCoreGLFW : public EngineCore
{
private:
	GLFWwindow* WindowID;
	static std::vector<bool> KeyBuffer;
	static const int KeyBufferSize = 400;

	GLuint VBO;
	GLuint VAO;
	GLuint FS;
	GLuint VS;
	GLuint ShaderProgram;

	int NumberOfTriangles = 4;

	static void MouseMoveCallbackEvent(GLFWwindow* window, double xPos, double yPos) {};
	static void KeyCallbackEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void WindowResizeCallbackEvent(GLFWwindow* window, int width, int height);

public:
	~EngineCoreGLFW() override;

	bool InitWindow(int Width, int Height, std::string WindowName) override;
	bool RunEngine(Game& GameID) override;
	void Draw() override;
};

