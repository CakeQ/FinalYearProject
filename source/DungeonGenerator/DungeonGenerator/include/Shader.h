#pragma once

#include <fstream>
#include <sstream>

#include <glfw3.h>

class Shader
{
private:


public:
	GLuint ui_ShaderProgram;
	
	Shader(const char *c_IVertexPath, const char *c_IFragmentPath);
	
	void Use();
};
