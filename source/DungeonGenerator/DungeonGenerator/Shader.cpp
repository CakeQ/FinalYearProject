#include <Shader.h>

#include <iostream>

Shader::Shader(const char *c_IVertexPath, const char *c_IFragmentPath)
{
	std::string s_VertexCode;
	std::string s_FragmentCode;
	std::ifstream is_VertexFile;
	std::ifstream is_FragmentFile;

	is_VertexFile.exceptions(std::ifstream::badbit);
	is_FragmentFile.exceptions(std::ifstream::badbit);

	is_VertexFile.open(c_IVertexPath);
	is_FragmentFile.open(c_IFragmentPath);

	if (!is_VertexFile || !is_FragmentFile)
	{
		std::cout << "ERROR: Shader files could not be loaded!" << std::endl;
		system("pause");
		return;
	}
	else {

		std::stringstream ss_VertexStream, ss_FragmentStream;

		ss_VertexStream << is_VertexFile.rdbuf();
		ss_FragmentStream << is_FragmentFile.rdbuf();

		is_VertexFile.close();
		is_FragmentFile.close();

		s_VertexCode = ss_VertexStream.str();
		s_FragmentCode = ss_FragmentStream.str();
	}

	const GLchar* c_VertexShaderCode[] = { s_VertexCode.c_str() };
	const GLchar* c_FragmentShaderCode[] = { s_FragmentCode.c_str() };

	int i_Success;
	char c_InfoLog[512];

	int i_Vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(i_Vertex, 1, c_VertexShaderCode, NULL);
	glCompileShader(i_Vertex);

	glGetShaderiv(i_Vertex, GL_COMPILE_STATUS, &i_Success);

	if (!i_Success)
	{
		glGetShaderInfoLog(i_Vertex, 512, NULL, c_InfoLog);
		std::cout << "ERROR: Vertex compilation failed:" << std::endl << c_InfoLog << std::endl;
	}

	int i_Fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(i_Fragment, 1, c_FragmentShaderCode, NULL);
	glCompileShader(i_Fragment);
	glGetShaderiv(i_Fragment, GL_COMPILE_STATUS, &i_Success);

	if (!i_Success)
	{
		glGetShaderInfoLog(i_Vertex, 512, NULL, c_InfoLog);
		std::cout << "ERROR: Fragment compilation failed:" << std::endl << c_InfoLog << std::endl;
	}

	ui_ShaderProgram = glCreateProgram();
	glAttachShader(ui_ShaderProgram, i_Vertex);
	glAttachShader(ui_ShaderProgram, i_Fragment);
	glLinkProgram(ui_ShaderProgram);

	glGetProgramiv(ui_ShaderProgram, GL_LINK_STATUS, &i_Success);
	if (!i_Success)
	{
		glGetShaderInfoLog(i_Vertex, 512, NULL, c_InfoLog);
		std::cout << "ERROR: Shader program linking failed:" << std::endl << c_InfoLog << std::endl;
	}

	glDeleteShader(i_Vertex);
	glDeleteShader(i_Fragment);

	Use();
}

void Shader::Use()
{
	glUseProgram(ui_ShaderProgram);
}