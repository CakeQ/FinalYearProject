/**
* \file EngineCoreGLFW.h
*/

//! GLFW engine core class.
/*!
GLFW engine class to which will be used if GLFW is enabled.
Created by Daniel Thompson, P15230940.
*/

#pragma once

#include <vector>

#include <EngineCoreBase.h>

#include <Model.h>
#include <Shader.h>
#include <CameraComponent.h>

class Game;

class EngineCoreGLFW : public EngineCore
{
private:
	GLFWwindow* w_WindowID;
	static std::vector<bool> vt_KeyBuffer;
	static const int i_KeyBufferSize = 400;
	
	static glm::vec2 v2_MouseBuffer;
	static bool b_FirstMouse;
	static float f_LastX;
	static float f_LastY;

	Shader* s_ShaderProgram;

	static void MouseMoveCallbackEvent(GLFWwindow* w_IWindow, double d_IXPos, double d_IYPos);
	static void KeyCallbackEvent(GLFWwindow* w_IWindow, int i_IKey, int i_IScanCode, int i_IAction, int i_IMods);
	static void WindowResizeCallbackEvent(GLFWwindow* i_IWindow, int i_IWidth, int i_IHeight);

public:
	EngineCoreGLFW();
	~EngineCoreGLFW() override;

	bool InitWindow(int i_IWidth, int i_IHeight, std::string i_IWindowName) override;
	bool RunEngine(Game& g_IGameID) override;

	Shader* GetShaderProgram() { return s_ShaderProgram; };

	void RenderColouredBackground(float f_IRed, float f_IGreen, float f_IBlue);
	void SetCamera(const CameraComponent* c_ICamera) override;
	void DrawCube(const glm::mat4& m4_IModelMatrix);
	void DrawModel(Model* model, glm::mat4& modelMatrix);
};

