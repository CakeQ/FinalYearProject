#pragma once

#include <glfw3.h>

#include <fstream>
#include <sstream>

class Shader
{
private:


public:
	GLuint ShaderProgram;
	
	Shader(const char *IVertexPath, const char *IFragmentPath);
	
	void Use();
};
