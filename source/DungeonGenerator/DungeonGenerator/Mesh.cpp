#include <stdafx.h>
#include <Mesh.h>

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

Mesh::Mesh(std::vector<Vertex> vt_IVertices, std::vector<GLuint> vt_IIndices, std::vector<Texture> vt_ITextures)
{
	vt_Vertices = vt_IVertices;
	vt_Indices = vt_IIndices;
	vt_Textures = vt_ITextures;

	SetUpMesh();
}

void Mesh::Draw(Shader* s_IShader)
{
	GLuint ui_DiffuseNum = 1;
	GLuint ui_SpecularNum = 1;

	for (GLuint i = 0; i < vt_Textures.size(); i++)
	{
		gl::ActiveTexture(gl::TEXTURE0 + i);
		std::stringstream SS;
		std::string Number;
		std::string Name = vt_Textures[i].s_Type;

		if (Name == "texture_diffuse")
		{
			SS << ui_DiffuseNum++;
		}
		else if (Name == "texture_specular")
		{
			SS << ui_SpecularNum++;
		}

		Number = SS.str();

		gl::Uniform1i(gl::GetUniformLocation(s_IShader->ui_ShaderProgram, (Name + Number).c_str()), i);
		gl::BindTexture(gl::TEXTURE_2D, vt_Textures[i].ui_ID);
	}
	
	gl::Uniform1f(gl::GetUniformLocation(s_IShader->ui_ShaderProgram, "material.shininess"), 16.0f);

	gl::BindVertexArray(ui_VAO);
	gl::DrawElements(gl::TRIANGLES, vt_Indices.size(), gl::UNSIGNED_INT, 0);
	gl::BindVertexArray(0);

	for (GLuint i = 0; i < vt_Textures.size(); i++)
	{
		gl::ActiveTexture(gl::TEXTURE0 + i);
		gl::BindTexture(gl::TEXTURE_2D, 0);
	}

}

void Mesh::SetUpMesh()
{
	gl::GenVertexArrays(1, &ui_VAO);																					//!< Generate the evertext array for the VAO.
	gl::GenBuffers(1, &ui_VBO);																							//!< Generate buffers for VBO.
	gl::GenBuffers(1, &ui_EBO);

	gl::BindVertexArray(ui_VAO);																						//!< Bind the VAO.

	gl::BindBuffer(gl::ARRAY_BUFFER, ui_VBO);																			//!< Bind the buffers for the VBO.
	gl::BufferData(gl::ARRAY_BUFFER, (vt_Indices.size() * sizeof(Vertex)), &vt_Vertices[0], gl::STATIC_DRAW);			//!< Buffer the triangle points in the VBO.

	gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, ui_EBO);
	gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, (vt_Indices.size() * sizeof(GLuint)), &vt_Indices[0], gl::STATIC_DRAW);
																														//!< Create a vertex array object.
	gl::EnableVertexAttribArray(0);																						//!< Enable the VAO.
	gl::VertexAttribPointer(0, 3, gl::FLOAT, FALSE, sizeof(Vertex), (GLvoid * )0);

	gl::EnableVertexAttribArray(1);																						//!< Apply normals.
	gl::VertexAttribPointer(1, 3, gl::FLOAT, FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, v3_Normal));

	gl::EnableVertexAttribArray(2);																						//!< Apply Texture coords.
	gl::VertexAttribPointer(2, 2, gl::FLOAT, FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, v2_TextureCoords));

	gl::BindVertexArray(0);
}
