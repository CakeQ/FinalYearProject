#pragma once

#include <glfw3.h>

#include <fstream>
#include <sstream>

class Shader
{
private:


public:
	GLuint ui_ShaderProgram;
	
	Shader(const char *c_IVertexPath, const char *c_IFragmentPath);
	
	void Use();
};
