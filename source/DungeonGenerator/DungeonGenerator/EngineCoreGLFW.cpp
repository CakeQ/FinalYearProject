
#include <stdafx.h>

#include <glm/detail/type_vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <EngineCoreGLFW.h>
#include <Game.h>

std::vector<bool> EngineCoreGLFW::KeyBuffer;

EngineCoreGLFW::EngineCoreGLFW() : ShaderProgram("../../../assets/shaders/basic.vs", "../../../assets/shaders/basic.frag")
{

}

EngineCoreGLFW::~EngineCoreGLFW()
{
	glfwTerminate();																								//!< Terminate the GLFW session.
}

bool EngineCoreGLFW::InitWindow(int IWidth, int IHeight, std::string IWindowName)
{
																													//!< Begin GLFW set-up.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);																	//!< Set GLFW version to 4.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);																	//!< Set GLFW version to 4.3.
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, TRUE);																//!< Set GLFW forward compatability to true.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);													//!< Set OpenGL profile to the core profile.
																													//!< End GLFW set-up.

																													//!< Begin Error handling.
	if (!glfwInit())																								//!< Terminates if there is no GLFW initialisation.
	{
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		glfwTerminate();
		return false;
	}

	WindowID = glfwCreateWindow(IWidth, IHeight, IWindowName.c_str(), nullptr, nullptr);							//!< Creates the window and assigns it to a reference ID integer so that it can be referenced later. Parameters are Width, Height, Window name, Fullscreen properties and mirroring.

	if (!WindowID)																									//!< Terminates if there is no window initialisation.
	{
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(WindowID);																				//!< Sets all future contexts to refer to current window until another context is made.

	gl::exts::LoadTest DidLoad = gl::sys::LoadFunctions();															//!< Attempt to load all GL functions.

	if (!DidLoad)																									//!< Terminates if GL functions fail to load.
	{
		fprintf(stderr, "ERROR: GLLoadGen failed to load functions\n");

		glfwTerminate();
		return false;
	}

	if (DidLoad.GetNumMissing() > 0)
	{
		printf("Number of functions that failed to load : %i.\n", DidLoad.GetNumMissing());							//!< Output number of GL functions that failed to load.
	}																												//!< End error handling.

	glfwSetFramebufferSizeCallback(WindowID, WindowResizeCallbackEvent);
	glfwSetKeyCallback(WindowID, KeyCallbackEvent);

	KeyBuffer.resize(KeyBufferSize);
	std::fill(KeyBuffer.begin(), KeyBuffer.end(), false);
	return true;
}

bool EngineCoreGLFW::RunEngine(Game& IGameID)
{
	IGameID.GameEngine = this;

	while (!glfwWindowShouldClose(WindowID)) {																		//!< Game loop.
		ShaderProgram.Use();

		IGameID.HandleInput(KeyBuffer);
		IGameID.Update();
		IGameID.Draw(ShaderProgram);

		glfwSwapBuffers(WindowID);
		glfwPollEvents();
	}

	return true;
}

void EngineCoreGLFW::KeyCallbackEvent(GLFWwindow* IWindow, int IKey, int IScanCode, int IAction, int IMods)
{
	if (IKey == GLFW_KEY_UNKNOWN || IKey > KeyBufferSize)
	{
		return;
	}

	KeyBuffer[IKey] = ((IAction == GLFW_PRESS || IAction == GLFW_REPEAT));

	if (glfwGetKey(IWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(IWindow, true);
	}
}

void EngineCoreGLFW::WindowResizeCallbackEvent(GLFWwindow* IWindow, int IWidth, int IHeight)
{
	// change the opengl viewport to match the new m_window size
	gl::Viewport(0, 0, IWidth, IHeight);
}

void EngineCoreGLFW::Draw(const glm::mat4& IModelMatrix)
{
	// set the model component of our shader to the cube model
	gl::UniformMatrix4fv(gl::GetUniformLocation(ShaderProgram.ShaderProgram, "model"), 1, gl::FALSE_, glm::value_ptr(IModelMatrix));

	// the only thing we can draw so far is the cube, so we know it is bound already
	// this will obviously have to change later
	gl::DrawArrays(gl::TRIANGLES, 0, 36);
}