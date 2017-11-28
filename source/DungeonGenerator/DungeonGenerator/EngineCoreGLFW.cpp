
#include <stdafx.h>

#include <glm/detail/type_vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <EngineCoreGLFW.h>
#include <Game.h>

std::vector<bool> EngineCoreGLFW::vt_KeyBuffer;
	
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

																																//!< Begin Error handling.
	if (!glfwInit())																											//!< Terminates if there is no GLFW initialisation.
	{
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		glfwTerminate();
		return false;
	}

	w_WindowID = glfwCreateWindow(i_IWidth, i_IHeight, s_IWindowName.c_str(), nullptr, nullptr);								//!< Creates the window and assigns it to a reference ID integer so that it can be referenced later. Parameters are Width, Height, Window name, Fullscreen properties and mirroring.

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
	glfwSetKeyCallback(w_WindowID, KeyCallbackEvent);

	s_ShaderProgram = new Shader("../../../assets/shaders/basic.vs", "../../../assets/shaders/basic.frag");						//!< Loads shaders.

	glm::mat4 Proj = glm::perspective(1.2f, (float)16 / 9, 0.1f, 100.0f);														//!< Creates projection matrix.
	gl::UniformMatrix4fv(gl::GetUniformLocation(s_ShaderProgram->ui_ShaderProgram, "projection"), 1, 0, glm::value_ptr(Proj));	//!< Sets projection matrix.

	glm::mat4 View = glm::lookAt(glm::vec3(0.0f, 0.0f, 4.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));		//!< Creates view matrix.
	gl::UniformMatrix4fv(gl::GetUniformLocation(s_ShaderProgram->ui_ShaderProgram, "view"), 1, 0, glm::value_ptr(View));		//!< Sets view matrix.

	vt_KeyBuffer.resize(i_KeyBufferSize);																						//!< Sets size of key buffer.
	std::fill(vt_KeyBuffer.begin(), vt_KeyBuffer.end(), false);																	//!< Fills key buffer.
	return true;
}

bool EngineCoreGLFW::RunEngine(Game& g_IGameID)
{
	g_IGameID.g_GameEngine = this;																								//!< Set game engine type.

	while (!glfwWindowShouldClose(w_WindowID))																					//!< Game loop.
	{
		s_ShaderProgram->Use();																									//!< Set shader program.

		g_IGameID.HandleInput(vt_KeyBuffer);																					//!< Handle any input.
		g_IGameID.Update();																										//!< Handle game updates.
		g_IGameID.Draw(s_ShaderProgram);																						//!< Draw everything.

		glfwSwapBuffers(w_WindowID);																							//!< Set window buffer.
		glfwPollEvents();																										//!< Check for any events.
	}

	return true;
}

void EngineCoreGLFW::KeyCallbackEvent(GLFWwindow* IWindow, int IKey, int IScanCode, int IAction, int IMods)
{
	if (IKey == GLFW_KEY_UNKNOWN || IKey > i_KeyBufferSize)
	{
		return;
	}

	vt_KeyBuffer[IKey] = ((IAction == GLFW_PRESS || IAction == GLFW_REPEAT));

	if (glfwGetKey(IWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(IWindow, true);
	}
}

void EngineCoreGLFW::WindowResizeCallbackEvent(GLFWwindow* IWindow, int IWidth, int IHeight)
{
	gl::Viewport(0, 0, IWidth, IHeight);																						//!< Change OpenGL viewport to match window size.
}

void EngineCoreGLFW::Draw(const glm::mat4& IModelMatrix)
{
	// set the model component of our shader to the cube model
	gl::UniformMatrix4fv(gl::GetUniformLocation(s_ShaderProgram->ui_ShaderProgram, "model"), 1, gl::FALSE_, glm::value_ptr(IModelMatrix));

	// the only thing we can draw so far is the cube, so we know it is bound already
	// this will obviously have to change later
	gl::DrawArrays(gl::TRIANGLES, 0, 36);
}