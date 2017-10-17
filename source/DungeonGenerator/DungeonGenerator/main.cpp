/**
* \file main.cpp
*/

//! Main game loop.
/*!
Main code file that contains the program's loop used to run everything else.
Created by Daniel Thompson, P15230940.
*/

#include "stdafx.h"

#include <gl_core_4_3.hpp>
#include <glfw3.h>

int _tmain(int argc, _TCHAR* argv[])
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
		return 1;
	}

	GLFWwindow* WindowID = glfwCreateWindow(640, 480, "GLEnvironment Test Environment", NULL, NULL);				//!< Creates the window and assigns it to a reference ID integer so that it can be referenced later. Parameters are Width, Height, Window name, Fullscreen properties and mirroring.

	if (!WindowID)																									//!< Terminates if there is no window initialisation.
	{
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(WindowID);																				//!< Sets all future contexts to refer to current window until another context is made.

	gl::exts::LoadTest DidLoad = gl::sys::LoadFunctions();															//!< Attempt to load all GL functions.

	if (!DidLoad)																									//!< Terminates if GL functions fail to load.
	{
		fprintf(stderr, "ERROR: GLLoadGen failed to load functions\n");

		glfwTerminate();
		return 1;
	}

	printf("Number of functions that failed to load : %i.\n", DidLoad.GetNumMissing());								//!< Output number of GL functions that failed to load.
																													//!< End error handling.

	int NumberOfTriangles = 4;

	float TrianglePoints[] = {																						//!< Create vertices of a points for triangles.
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


	GLuint VBO = 0;																									//!< Create a vertex buffer object to hold this data.
	gl::GenBuffers(1, &VBO);																						//!< Generate buffers for VBO.
	gl::BindBuffer(gl::ARRAY_BUFFER, VBO);																			//!< Bind the buffers for the VBO.
	gl::BufferData(gl::ARRAY_BUFFER, ((9 * sizeof(float))* NumberOfTriangles), TrianglePoints, gl::STATIC_DRAW);	//!< Buffer the triangle points in the VBO.

	GLuint VAO = 0;																									//!< Create a vertex array object.
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

	GLuint VS = gl::CreateShader(gl::VERTEX_SHADER);																//!< Create the shader sources.
	gl::ShaderSource(VS, 1, &VertexShader, NULL);
	gl::CompileShader(VS);

	GLuint FS = gl::CreateShader(gl::FRAGMENT_SHADER);
	gl::ShaderSource(FS, 1, &FragmentShader, NULL);
	gl::CompileShader(FS);

	GLuint shader_program = gl::CreateProgram();																	//!< Create shader program.
	gl::AttachShader(shader_program, FS);
	gl::AttachShader(shader_program, VS);
	gl::LinkProgram(shader_program);

	while (!glfwWindowShouldClose(WindowID)) {																		//!< Draw loop.
		gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);														//!< Clear previous frame.
		gl::UseProgram(shader_program);																				//!< Assign shader program.
		gl::BindVertexArray(VAO);																					//!< Bind VAO to the vertex array.

		gl::DrawArrays(gl::TRIANGLES, 0, (3 * NumberOfTriangles));													//!< Draw all triangles.

		glfwPollEvents();

		glfwSwapBuffers(WindowID);
	}

	glfwTerminate();																								//!< Terminate the GLFW session.

	return 0;																										//!< Exit program.
}