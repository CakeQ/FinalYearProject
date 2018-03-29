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
	//!< Begin GLFW Initialization																															//!< Begin GLFW set-up.
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

	//glfwSetInputMode(w_WindowID, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	vt_KeyBuffer.resize(i_KeyBufferSize);																						//!< Sets size of key buffer.
	std::fill(vt_KeyBuffer.begin(), vt_KeyBuffer.end(), false);																	//!< Fills key buffer.

	s_DefaultShaderProgram = new Shader("assets/shaders/defaultShader.vert", "assets/shaders/defaultShader.frag");				//!< Loads default shaders.
	//s_FontshaderProgram = new Shader("assets/shaders/fontShader.vert", "assets/shaders/fontShader.frag");						//!< Loads font shaders.
	SetupDefaultFont();

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
		//RenderText(s_FrameText, 0.005f, 0.95f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
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
	std::cout << i_IButton << ", " << i_IAction << std::endl;
	int i_State;
	
}

void EngineCoreGLFW::WindowResizeCallbackEvent(GLFWwindow* w_IWindow, int i_IWidth, int i_IHeight)
{
	i_Width = i_IWidth;
	i_Height = i_IHeight;
	glViewport(0, 0, i_IWidth, i_IHeight);																					//!< Change OpenGL viewport to match window size.
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

void EngineCoreGLFW::RenderText(std::string text, float x, float y, float scale, glm::vec3 colour)
{
	// set the window to orthographic
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(i_Width), 0.0f, static_cast<float>(i_Height));

	float f_PixelValueX = x * i_Width;
	float f_PixelValueY = y * i_Height;

	glUseProgram(s_FontshaderProgram->ui_ShaderProgram);
	glUniformMatrix4fv(glGetUniformLocation(s_FontshaderProgram->ui_ShaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	// Activate corresponding render state	
	glUniform3f(glGetUniformLocation(s_FontshaderProgram->ui_ShaderProgram, "textColour"), colour.x, colour.y, colour.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(ui_FontVAO);

	// Iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = m_Characters[*c];

		GLfloat f_XPos = f_PixelValueX + ch.v2_Bearing.x * scale;
		GLfloat f_Ypos = f_PixelValueY - (ch.v2_Size.y - ch.v2_Bearing.y) * scale;

		GLfloat w = ch.v2_Size.x * scale;
		GLfloat h = ch.v2_Size.y * scale;
		// Update VBO for each character
		GLfloat vertices[6][4] = {
			{ f_XPos,     f_Ypos + h,   0.0, 0.0 },
			{ f_XPos,     f_Ypos,       0.0, 1.0 },
			{ f_XPos + w, f_Ypos,       1.0, 1.0 },

			{ f_XPos,     f_Ypos + h,   0.0, 0.0 },
			{ f_XPos + w, f_Ypos,       1.0, 1.0 },
			{ f_XPos + w, f_Ypos + h,   1.0, 0.0 }
		};
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.ui_TextureID);
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, ui_FontVBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		f_PixelValueX += (ch.ui_Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	// go back to default shader
	glUseProgram(s_DefaultShaderProgram->ui_ShaderProgram);
}

void EngineCoreGLFW::DrawCube(const glm::mat4& m4_IModelMatrix)
{
	// set the model component of our shader to the cube model
	glUniformMatrix4fv(glGetUniformLocation(s_DefaultShaderProgram->ui_ShaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(m4_IModelMatrix));

	// the only thing we can draw so far is the cube, so we know it is bound already
	// this will obviously have to change later
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void EngineCoreGLFW::DrawDebug(PhysicsComponent* c_PhysicsComponent, const glm::mat4& m4_IModelMatrix)
{
	// set the model component of our shader to the cube model
	glUniformMatrix4fv(glGetUniformLocation(s_DefaultShaderProgram->ui_ShaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(m4_IModelMatrix));

	// the only thing we can draw so far is the cube, so we know it is bound already
	// this will obviously have to change later

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if (c_PhysicsComponent)
	{
		c_PhysicsComponent->Draw(s_DefaultShaderProgram, m4_IModelMatrix);
	}
	else
	{
		std::cout << "ERROR: Model is NULL" << std::endl;
	}
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

void EngineCoreGLFW::SetupDefaultFont()
{
	// FreeType
	FT_Library ft;
	// All functions return a value different than 0 whenever an error occurred
	if (FT_Init_FreeType(&ft))
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

	// Load font as face
	FT_Face face;
	if (FT_New_Face(ft, "Assets/Fonts/Pixeled.ttf", 0, &face))
	{
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
		return;
	}
	else
	{
		std::cout << "Loaded default font" << std::endl;
	}
	// Set size to load glyphs as
	FT_Set_Pixel_Sizes(face, 0, 48);

	// Disable byte-alignment restriction
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Load first 128 characters of ASCII set
	for (GLubyte c = 0; c < 128; c++)
	{
		// Load character glyph 
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Now store character for later use
		Character character = 
		{
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		m_Characters.insert(std::pair<GLchar, Character>(c, character));
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	// Destroy FreeType once we're finished
	FT_Done_Face(face);
	FT_Done_FreeType(ft);


	// Configure VAO/VBO for texture quads
	glGenVertexArrays(1, &ui_FontVAO);
	glGenBuffers(1, &ui_FontVBO);
	glBindVertexArray(ui_FontVBO);
	glBindBuffer(GL_ARRAY_BUFFER, ui_FontVBO);
	// dynamic draw as the text may change frequently
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}