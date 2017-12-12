#include <stdafx.h>

#include <Shader.h>

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

	const GLchar *c_VertexShaderCode[] = { s_VertexCode.c_str() };
	const GLchar *c_FragmentShaderCode[] = { s_FragmentCode.c_str() };

	int i_Success;
	char c_InfoLog[512];

	int i_Vertex = gl::CreateShader(gl::VERTEX_SHADER);
	gl::ShaderSource(i_Vertex, 1, c_VertexShaderCode, NULL);
	gl::CompileShader(i_Vertex);

	gl::GetShaderiv(i_Vertex, gl::COMPILE_STATUS, &i_Success);

	if (!i_Success)
	{
		gl::GetShaderInfoLog(i_Vertex, 512, NULL, c_InfoLog);
		std::cout << "ERROR: Vertex compilation failed:" << std::endl << c_InfoLog << std::endl;
	}

	int i_Fragment = gl::CreateShader(gl::FRAGMENT_SHADER);
	gl::ShaderSource(i_Fragment, 1, c_FragmentShaderCode, NULL);
	gl::CompileShader(i_Fragment);
	gl::GetShaderiv(i_Fragment, gl::COMPILE_STATUS, &i_Success);

	if (!i_Success)
	{
		gl::GetShaderInfoLog(i_Vertex, 512, NULL, c_InfoLog);
		std::cout << "ERROR: Fragment compilation failed:" << std::endl << c_InfoLog << std::endl;
	}

	ui_ShaderProgram = gl::CreateProgram();
	gl::AttachShader(ui_ShaderProgram, i_Vertex);
	gl::AttachShader(ui_ShaderProgram, i_Fragment);
	gl::LinkProgram(ui_ShaderProgram);

	gl::GetProgramiv(ui_ShaderProgram, gl::LINK_STATUS, &i_Success);
	if (!i_Success)
	{
		gl::GetShaderInfoLog(i_Vertex, 512, NULL, c_InfoLog);
		std::cout << "ERROR: Shader program linking failed:" << std::endl << c_InfoLog << std::endl;
	}

	gl::DeleteShader(i_Vertex);
	gl::DeleteShader(i_Fragment);

	Use();
}

void Shader::Use()
{
	gl::UseProgram(ui_ShaderProgram);
}