#include <stdafx.h>

#include <Shader.h>

Shader::Shader(const char *IVertexPath, const char *IFragmentPath)
{
	std::string VertexCode;
	std::string FragmentCode;
	std::ifstream VertexFile;
	std::ifstream FragmentFile;

	VertexFile.exceptions(std::ifstream::badbit);
	FragmentFile.exceptions(std::ifstream::badbit);

	try
	{
		VertexFile.open(IVertexPath);
		FragmentFile.open(IFragmentPath);

		std::stringstream VertexStream, FragmentStream;

		VertexStream << VertexFile.rdbuf();
		FragmentStream << FragmentFile.rdbuf();

		VertexFile.close();
		FragmentFile.close();

		VertexCode = VertexStream.str();
		FragmentCode = FragmentStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR: Shader files could not be loaded!" << std::endl;
	}

	const GLchar *VertexShaderCode = VertexCode.c_str();
	const GLchar *FragmentShaderCode = FragmentCode.c_str();

	GLuint Vertex, Fragment;
	GLint Success;
	GLchar InfoLog[512];

	Vertex = gl::CreateShader(gl::VERTEX_SHADER);
	gl::ShaderSource(Vertex, 1, &VertexShaderCode, NULL);
	gl::CompileShader(Vertex);

	gl::GetShaderiv(Vertex, gl::COMPILE_STATUS, &Success);

	if (!Success)
	{
		gl::GetShaderInfoLog(Vertex, 512, NULL, InfoLog);
		std::cout << "ERROR: Vertex compilation failed:" << std::endl << InfoLog << std::endl;
	}

	Fragment = gl::CreateShader(gl::FRAGMENT_SHADER);
	gl::ShaderSource(Fragment, 1, &FragmentShaderCode, NULL);
	gl::CompileShader(Fragment);
	gl::GetShaderiv(Fragment, gl::COMPILE_STATUS, &Success);

	if (!Success)
	{
		gl::GetShaderInfoLog(Vertex, 512, NULL, InfoLog);
		std::cout << "ERROR: Fragment compilation failed:" << std::endl << InfoLog << std::endl;
	}

	ShaderProgram = gl::CreateProgram();
	gl::AttachShader(ShaderProgram, Vertex);
	gl::AttachShader(ShaderProgram, Fragment);
	gl::LinkProgram(ShaderProgram);

	gl::GetProgramiv(ShaderProgram, gl::LINK_STATUS, &Success);
	if (!Success)
	{
		gl::GetShaderInfoLog(Vertex, 512, NULL, InfoLog);
		std::cout << "ERROR: Shader program linking failed:" << std::endl << InfoLog << std::endl;
	}

	gl::DeleteShader(Vertex);
	gl::DeleteShader(Fragment);
}

void Shader::Use()
{
	gl::UseProgram(ShaderProgram);
}