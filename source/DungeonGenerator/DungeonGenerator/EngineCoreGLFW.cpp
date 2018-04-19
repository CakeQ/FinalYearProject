#include <EngineCoreGLFW.h>

#include "Game.h"
#include "Component.h"
#include "CameraComponent.h"
#include "PhysicsComponent.h"
#include "Entity.h"

std::vector<bool> EngineCoreGLFW::vt_KeyBuffer;
glm::vec2 EngineCoreGLFW::v2_MouseBuffer;
glm::vec2 EngineCoreGLFW::v2_LastMousePos;
bool EngineCoreGLFW::b_FirstMouse;

int EngineCore::i_Width;
int EngineCore::i_Height;

EngineCoreGLFW::~EngineCoreGLFW()
{
	glfwTerminate();																											//!< Terminate the GLFW session.
}

bool EngineCoreGLFW::InitWindow(int i_IWidth, int i_IHeight, std::string s_IWindowName)											//!< Window Initialisation.
{
	//!< Begin GLFW Initialization																								//!< Begin GLFW set-up.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);																				//!< Set GLFW version to 4.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);																				//!< Set GLFW version to 4.3.
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, TRUE);																			//!< Set GLFW forward compatability to true.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);																//!< Set OpenGL profile to the core profile.
																																//!< End GLFW set-up.
	i_Width = i_IWidth;
	i_Height = i_IHeight;
																																//!< Begin Error handling.
	if (!glfwInit())																											//!< Terminates if there is no GLFW initialisation.
	{
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		glfwTerminate();
		return false;
	}

	w_WindowID = glfwCreateWindow(i_Width, i_Height, s_IWindowName.c_str(), nullptr, nullptr);									//!< Creates the window and assigns it to a reference ID integer so that it can be referenced later.
																																//!<Parameters are Width, Height, Window name, Fullscreen properties and mirroring.

	if (!w_WindowID)																											//!< Terminates if there is no window initialisation.
	{
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return false;
	}

	ImGui::CreateContext();																										//!< Set-Up ImGUI binding.
	ImGui_ImplGlfwGL3_Init(w_WindowID, true);																					//!< Initialise ImGUI.

	glfwMakeContextCurrent(w_WindowID);																							//!< Sets all future contexts to refer to current window until another context is made.

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialise GLAD" << std::endl;
		return false;
	}																											
																																//!< End error handling.

	glfwSetFramebufferSizeCallback(w_WindowID, WindowResizeCallbackEvent);
	glfwSetCursorPosCallback(w_WindowID, MouseMoveCallbackEvent);
	glfwSetMouseButtonCallback(w_WindowID, MouseButtonCallBackEvent);
	glfwSetKeyCallback(w_WindowID, KeyCallbackEvent);

	vt_KeyBuffer.resize(i_KeyBufferSize);																						//!< Sets size of key buffer.
	std::fill(vt_KeyBuffer.begin(), vt_KeyBuffer.end(), false);																	//!< Fills key buffer.

	s_DefaultShaderProgram = new Shader("assets/shaders/defaultShader.vert", "assets/shaders/defaultShader.frag");				//!< Loads default shaders.

	glEnable(GL_DEPTH_TEST);																									//!< Enable depth testing.

	glEnable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	return true;
}

bool EngineCoreGLFW::RunEngine(Game& g_IGameID)
{
	double d_SimulationTime = glfwGetTime();
	double d_DeltaTime = 1.0 / 60.0;
	int i_FrameRate = 0;

	g_IGameID.e_GameEngine = this;																								//!< Set game engine type.
	g_IGameID.Initialise();																										//!< Initialise game.

	while (!glfwWindowShouldClose(w_WindowID))																					//!< Game loop.
	{
		ImGui_ImplGlfwGL3_NewFrame();																							//!< Call new ImGUI frame.
		double d_RealTime = glfwGetTime();																						//!< Get current CPU time.

		g_IGameID.s_CurrentScene->ih_InputHandler->handleInputs(vt_KeyBuffer, v2_MouseBuffer);									//!< Handle game input.
		v2_MouseBuffer = glm::vec2(0.0f, 0.0f);																					//!< Reset mouse buffer.
		glfwGetFramebufferSize(w_WindowID, &i_Width, &i_Height);																//!< Update window dimensions.

		g_IGameID.s_CurrentScene->DrawGUI();

		while (d_SimulationTime < d_RealTime)
		{
			d_SimulationTime += d_DeltaTime;
			g_IGameID.Update(d_DeltaTime);																						//!< Handle game updates.
			i_FrameRate++;																										//!< Incriment framerate count.
		}

		g_IGameID.Draw();																										//!< Draw everything.
		
		ImGui::Render();																										//!< Render ImGUI.
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());																	//!< Render GLFW ImGUI implementation.

		double d_FrameRate = 1000.0 / double(i_FrameRate);
		std::string s_FrameText = std::to_string(d_FrameRate) + " FPS";
		i_FrameRate = 0;

		glfwSwapBuffers(w_WindowID);																							//!< Swap window buffer.
		glfwPollEvents();																										//!< Check for any events.
	}

	return true;
}

void EngineCoreGLFW::KeyCallbackEvent(GLFWwindow* w_IWindow, int i_IKey, int i_IScanCode, int i_IAction, int i_IMods)
{
	if (i_IKey == GLFW_KEY_UNKNOWN || i_IKey > i_KeyBufferSize)
	{
		return;
	}

	vt_KeyBuffer[i_IKey] = ((i_IAction == GLFW_PRESS || i_IAction == GLFW_REPEAT));

	if (glfwGetKey(w_IWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(w_IWindow, true);
	}
}

void EngineCoreGLFW::MouseMoveCallbackEvent(GLFWwindow* w_IWindow, double d_IXPos, double d_IYPos)
{
	if (b_FirstMouse)
	{
		v2_LastMousePos = glm::vec2(d_IXPos, d_IYPos);
		b_FirstMouse = false;
	}

	glm::vec2 v2_Offset = glm::vec2(d_IXPos - v2_LastMousePos.x, v2_LastMousePos.y - d_IYPos);

	v2_LastMousePos = glm::vec2(d_IXPos, d_IYPos);

	v2_MouseBuffer = v2_Offset;
}

void EngineCoreGLFW::MouseButtonCallBackEvent(GLFWwindow * w_IWindow, int i_IButton, int i_IAction, int i_iMods)
{

}

void EngineCoreGLFW::WindowResizeCallbackEvent(GLFWwindow* w_IWindow, int i_IWidth, int i_IHeight)
{
	i_Width = i_IWidth;
	i_Height = i_IHeight;
	glViewport(0, 0, i_IWidth, i_IHeight);														//!< Change OpenGL viewport to match window size.
}

void EngineCoreGLFW::SetCamera(const CameraComponent* c_ICamera)
{
	// set the view and projection components of our shader to the camera values
	glm::mat4 m4_Projection = glm::perspective(glm::radians(c_ICamera->f_FOV), (float)i_Width / (float)i_Height, 0.1f, 100000.0f);
	glUniformMatrix4fv(glGetUniformLocation(s_DefaultShaderProgram->ui_ShaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(m4_Projection));

	glUniformMatrix4fv(glGetUniformLocation(s_DefaultShaderProgram->ui_ShaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(c_ICamera->GetViewMatrix()));

	// be sure to activate shader when setting uniforms/drawing objects
	glUniform3f(glGetUniformLocation(s_DefaultShaderProgram->ui_ShaderProgram, "objectColour"), 1.0f, 0.6f, 0.61f);
	glUniform3f(glGetUniformLocation(s_DefaultShaderProgram->ui_ShaderProgram, "lightColour"), 1.0f, 1.0f, 1.0f);
	glUniform3f(glGetUniformLocation(s_DefaultShaderProgram->ui_ShaderProgram, "lightPos"), 0.0f, 2.0f, -2.0f);
	glUniform3fv(glGetUniformLocation(s_DefaultShaderProgram->ui_ShaderProgram, "viewPos"), 1, glm::value_ptr(c_ICamera->GetPosition()));

}

void EngineCoreGLFW::RenderColouredBackground(float f_IRed, float f_IGreen, float f_IBlue)
{
	glClearColor(f_IRed, f_IGreen, f_IBlue, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void EngineCoreGLFW::DrawCube(const glm::mat4& m4_IModelMatrix)
{
	// set the model component of our shader to the cube model
	glUniformMatrix4fv(glGetUniformLocation(s_DefaultShaderProgram->ui_ShaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(m4_IModelMatrix));

	// the only thing we can draw so far is the cube, so we know it is bound already
	// this will obviously have to change later
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void EngineCoreGLFW::DrawModel(Model* m_IModel, glm::mat4& m4_IModelMatrix)
{
	if (m_IModel)
	{
		m_IModel->Draw(s_DefaultShaderProgram, m4_IModelMatrix);
	}
	else
	{
		std::cout << "ERROR: Model is NULL" << std::endl;
	}
}