
#include <stdafx.h>
#include <Game.h>
#include <EngineCoreGLFW.h>

std::vector<bool> EngineCoreGLFW::KeyBuffer;

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
	float TrianglePoints[] = {
		-0.15f, 0.5f, 0.0f,
		0.10f, -0.5f, 0.0f,
		-0.15f, -0.5f, 0.0f,

		-0.4f, 0.5f, 0.0f,
		-0.15f, 0.5f, 0.0f,
		-0.15f, -0.5f, 0.0f,

		0.15f, 0.5f, 0.0f,
		0.15f, -0.5f, 0.0f,
		-0.1f, -0.5f, 0.0f,

		0.15f, 0.5f, 0.0f,
		0.4f, 0.5f, 0.0f,
		0.15f, -0.5f, 0.0f
	};

	if (DidLoad.GetNumMissing() > 0)
	{
		printf("Number of functions that failed to load : %i.\n", DidLoad.GetNumMissing());								//!< Output number of GL functions that failed to load.
	}																											//!< End error handling.

	glfwSetFramebufferSizeCallback(WindowID, WindowResizeCallbackEvent);
	glfwSetKeyCallback(WindowID, KeyCallbackEvent);

	KeyBuffer.resize(KeyBufferSize);
	std::fill(KeyBuffer.begin(), KeyBuffer.end(), false);

	VBO = 0;																										//!< Create a vertex buffer object to hold this data.
	gl::GenBuffers(1, &VBO);																						//!< Generate buffers for VBO.
	gl::BindBuffer(gl::ARRAY_BUFFER, VBO);																			//!< Bind the buffers for the VBO.
	gl::BufferData(gl::ARRAY_BUFFER, ((9 * sizeof(float))* NumberOfTriangles), TrianglePoints, gl::STATIC_DRAW);	//!< Buffer the triangle points in the VBO.

	VAO = 0;																										//!< Create a vertex array object.
	gl::GenVertexArrays(1, &VAO);																					//!< Generate the evertext array for the VAO.
	gl::BindVertexArray(VAO);																						//!< Bind the VAO.
	gl::EnableVertexAttribArray(0);																					//!< Enable the VAO.
	gl::BindBuffer(gl::ARRAY_BUFFER, VAO);																			//!< Bind the VAO to the buffer.
	gl::VertexAttribPointer(0, 3, gl::FLOAT, FALSE, 0, NULL);


	const char* VertexShader =																						//!< Create vertex shader.
		"#version 400\n"
		"in vec3 vp;"
		"void main()"
		"{"
		"	gl_Position = vec4(vp, 1.0);"
		"}";

	const char* FragmentShader =																					//!< Create fragment shader.
		"#version 400\n"
		"out vec4 frag_colour;"
		"void main() "
		"{"
		" frag_colour = vec4(0.0, 0.0, 1.0, 1.0); "
		"}";

	VS = gl::CreateShader(gl::VERTEX_SHADER);																		//!< Create the shader sources.
	gl::ShaderSource(VS, 1, &VertexShader, NULL);
	gl::CompileShader(VS);

	FS = gl::CreateShader(gl::FRAGMENT_SHADER);
	gl::ShaderSource(FS, 1, &FragmentShader, NULL);
	gl::CompileShader(FS);

	ShaderProgram = gl::CreateProgram();																			//!< Create shader program.
	gl::AttachShader(ShaderProgram, FS);
	gl::AttachShader(ShaderProgram, VS);
	gl::LinkProgram(ShaderProgram);

	return true;
}

bool EngineCoreGLFW::RunEngine(Game& IGameID)
{
	IGameID.GameEngine = this;

	while (!glfwWindowShouldClose(WindowID)) {																		//!< Draw loop.
		IGameID.HandleInput(KeyBuffer);
		IGameID.Update();
		IGameID.Draw();

		glfwSwapBuffers(WindowID);
		glfwPollEvents();
	}

	return true;
}

void EngineCoreGLFW::Draw()
{
	gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);														//!< Clear previous frame.
	gl::UseProgram(ShaderProgram);																				//!< Assign shader program.
	gl::BindVertexArray(VAO);																					//!< Bind VAO to the vertex array.

	gl::DrawArrays(gl::TRIANGLES, 0, (3 * NumberOfTriangles));													//!< Draw all triangles.

}

void EngineCoreGLFW::KeyCallbackEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_UNKNOWN || key > KeyBufferSize)
	{
		return;
	}

	KeyBuffer[key] = ((action == GLFW_PRESS || action == GLFW_REPEAT));

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void EngineCoreGLFW::WindowResizeCallbackEvent(GLFWwindow* IWindow, int IWidth, int IHeight)
{
	// change the opengl viewport to match the new m_window size
	gl::Viewport(0, 0, IWidth, IHeight);
}