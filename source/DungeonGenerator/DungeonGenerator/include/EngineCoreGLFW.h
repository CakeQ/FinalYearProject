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

#include "EngineCoreBase.h"

#include "Model.h"
#include "Shader.h"
#include "CameraComponent.h"

class Game;

class EngineCoreGLFW : public EngineCore
{
private:
	GLFWwindow* w_WindowID;
	static std::vector<bool> vt_KeyBuffer;
	static const int i_KeyBufferSize = 400;
	
	static glm::vec2 v2_MouseBuffer;
	static bool b_FirstMouse;
	static glm::vec2 v2_LastMousePos;

	Shader* s_DefaultShaderProgram;
	Shader* s_FontshaderProgram;

	struct Character {
		GLuint ui_TextureID;   // ID handle of the glyph texture
		glm::ivec2 v2_Size;    // Size of glyph
		glm::ivec2 v2_Bearing;  // Offset from baseline to left/top of glyph
		GLuint ui_Advance;    // Horizontal offset to advance to next glyph
	};

	std::map<GLchar, Character> m_Characters;
	GLuint ui_FontVAO, ui_FontVBO;

	static void MouseMoveCallbackEvent(GLFWwindow* w_IWindow, double d_IXPos, double d_IYPos);
	static void KeyCallbackEvent(GLFWwindow* w_IWindow, int i_IKey, int i_IScanCode, int i_IAction, int i_IMods);
	static void WindowResizeCallbackEvent(GLFWwindow* i_IWindow, int i_IWidth, int i_IHeight);

public:
	~EngineCoreGLFW() override;

	bool InitWindow(int i_IWidth, int i_IHeight, std::string i_IWindowName) override;
	bool RunEngine(Game& g_IGameID) override;
	void SetCamera(const CameraComponent* c_ICamera) override;

	void RenderColouredBackground(float f_IRed, float f_IGreen, float f_IBlue) override;
	void RenderText(std::string text, float x, float y, float scale, glm::vec3 colour) override;

	void DrawCube(const glm::mat4& m4_IModelMatrix) override;
	void DrawModel(Model* model, glm::mat4& modelMatrix) override;

	void EngineCoreGLFW::SetupDefaultFont();
};

