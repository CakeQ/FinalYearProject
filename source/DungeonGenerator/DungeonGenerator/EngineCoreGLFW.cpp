
#include <stdafx.h>

#include <EngineCoreGLFW.h>

#include <glm/detail/type_vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Game.h>
#include <Component.h>
#include <CameraComponent.h>
#include <Entity.h>

std::vector<bool> EngineCoreGLFW::vt_KeyBuffer;
glm::vec2 EngineCoreGLFW::v2_MouseBuffer;
bool EngineCoreGLFW::b_FirstMouse;
float EngineCoreGLFW::f_LastX;
float EngineCoreGLFW::f_LastY;
int EngineCore::i_Width;
int EngineCore::i_Height;

EngineCoreGLFW::EngineCoreGLFW()																								//!< Constructor.
{

}

EngineCoreGLFW::~EngineCoreGLFW()
{
	glfwTerminate();																											//!< Terminate the GLFW session.
}

bool EngineCoreGLFW::InitWindow(int i_IWidth, int i_IHeight, std::string s_IWindowName)											//!< Window Initialisation.
{
																																//!< Begin GLFW set-up.
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

	w_WindowID = glfwCreateWindow(i_Width, i_Height, s_IWindowName.c_str(), nullptr, nullptr);									//!< Creates the window and assigns it to a reference ID integer so that it can be referenced later. Parameters are Width, Height, Window name, Fullscreen properties and mirroring.

	if (!w_WindowID)																											//!< Terminates if there is no window initialisation.
	{
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(w_WindowID);																							//!< Sets all future contexts to refer to current window until another context is made.

	gl::exts::LoadTest lt_DidLoad = gl::sys::LoadFunctions();																	//!< Attempt to load all GL functions.

	if (!lt_DidLoad)																											//!< Terminates if GL functions fail to load.
	{
		fprintf(stderr, "ERROR: GLLoadGen failed to load functions\n");

		glfwTerminate();
		return false;
	}

	if (lt_DidLoad.GetNumMissing() > 0)
	{
		printf("Number of functions that failed to load : %i.\n", lt_DidLoad.GetNumMissing());									//!< Output number of GL functions that failed to load.
	}																															//!< End error handling.

	glfwSetFramebufferSizeCallback(w_WindowID, WindowResizeCallbackEvent);
	
	glfwSetCursorPosCallback(w_WindowID, MouseMoveCallbackEvent);
	glfwSetKeyCallback(w_WindowID, KeyCallbackEvent);

	vt_KeyBuffer.resize(i_KeyBufferSize);																						//!< Sets size of key buffer.
	std::fill(vt_KeyBuffer.begin(), vt_KeyBuffer.end(), false);																	//!< Fills key buffer.

	s_ShaderProgram = new Shader("assets/shaders/basic.vert", "assets/shaders/basic.frag");										//!< Loads shaders.																							

	gl::Enable(gl::DEPTH_TEST);																									//!< Enable depth testing.

	return true;
}

bool EngineCoreGLFW::RunEngine(Game& g_IGameID)
{
	g_IGameID.g_GameEngine = this;																								//!< Set game engine type.
	g_IGameID.SetUpScene();

	while (!glfwWindowShouldClose(w_WindowID))																					//!< Game loop.
	{
		g_IGameID.Update();																										//!< Handle game updates.
		g_IGameID.Draw();																										//!< Draw everything.

		glfwSwapBuffers(w_WindowID);																							//!< Set window buffer.
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
		f_LastX = d_IXPos;
		f_LastY = d_IYPos;
		b_FirstMouse = false;
	}

	GLfloat f_XOffset = d_IXPos - f_LastX;
	GLfloat f_YOffset = f_LastY - d_IYPos;  // Reversed since y-coordinates go from bottom to left

	f_LastX = d_IXPos;
	f_LastY = d_IYPos;

	v2_MouseBuffer = glm::vec2(f_XOffset, f_YOffset);
}

void EngineCoreGLFW::WindowResizeCallbackEvent(GLFWwindow* w_IWindow, int i_IWidth, int i_IHeight)
{
	i_Width = i_IWidth;
	i_Height = i_IHeight;
	gl::Viewport(0, 0, i_IWidth, i_IHeight);																					//!< Change OpenGL viewport to match window size.
}

void EngineCoreGLFW::SetCamera(const CameraComponent* c_ICamera)
{
	// set the view and projection components of our shader to the camera values
	glm::mat4 m4_Projection = glm::perspective(glm::radians(c_ICamera->f_FOV), (float)i_Width / (float)i_Height, 0.1f, 100.0f);
	gl::UniformMatrix4fv(gl::GetUniformLocation(s_ShaderProgram->ui_ShaderProgram, "projection"), 1, gl::FALSE_, glm::value_ptr(m4_Projection));

	gl::UniformMatrix4fv(gl::GetUniformLocation(s_ShaderProgram->ui_ShaderProgram, "view"), 1, gl::FALSE_, glm::value_ptr(c_ICamera->GetViewMatrix()));

	// be sure to activate shader when setting uniforms/drawing objects
	gl::Uniform3f(gl::GetUniformLocation(s_ShaderProgram->ui_ShaderProgram, "objectColour"), 1.0f, 0.6f, 0.61f);
	gl::Uniform3f(gl::GetUniformLocation(s_ShaderProgram->ui_ShaderProgram, "lightColour"), 1.0f, 1.0f, 1.0f);
	gl::Uniform3f(gl::GetUniformLocation(s_ShaderProgram->ui_ShaderProgram, "lightPos"), 0.0f, 2.0f, -2.0f);
	gl::Uniform3fv(gl::GetUniformLocation(s_ShaderProgram->ui_ShaderProgram, "viewPos"), 1, glm::value_ptr(c_ICamera->GetPosition()));

}

void EngineCoreGLFW::RenderColouredBackground(float f_IRed, float f_IGreen, float f_IBlue)
{
	gl::ClearColor(f_IRed, f_IGreen, f_IBlue, 1.0f);
	gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);
}

void EngineCoreGLFW::DrawCube(const glm::mat4& m4_IModelMatrix)
{
	// set the model component of our shader to the cube model
	gl::UniformMatrix4fv(gl::GetUniformLocation(s_ShaderProgram->ui_ShaderProgram, "model"), 1, gl::FALSE_, glm::value_ptr(m4_IModelMatrix));

	// the only thing we can draw so far is the cube, so we know it is bound already
	// this will obviously have to change later
	gl::DrawArrays(gl::TRIANGLES, 0, 36);
}

void EngineCoreGLFW::DrawModel(Model* m_IModel, glm::mat4& m4_IModelMatrix)
{
	// set the model component of our shader to the object model
	gl::UniformMatrix4fv(gl::GetUniformLocation(s_ShaderProgram->ui_ShaderProgram, "model"), 1, gl::FALSE_, glm::value_ptr(m4_IModelMatrix));

	m_IModel->Draw(s_ShaderProgram);
}