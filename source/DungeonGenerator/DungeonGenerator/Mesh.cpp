#include <stdafx.h>

#include <Mesh.h>


Mesh::Mesh(std::vector<Vertex> IVertices, std::vector<GLuint> IIndices, std::vector<Texture> ITextures)
{
	Vertices = IVertices;
	Indices = IIndices;
	Textures = ITextures;
}

void Mesh::Draw(GLuint IShaderProgram)
{
	GLuint DiffuseNr = 1;
	GLuint SpecularNr = 1;

	for (GLuint i = 0; i < Textures.size(); i++)
	{
		gl::ActiveTexture(gl::TEXTURE0 + i);
		std::stringstream SS;
		std::string Number;
		std::string Name = Textures[i].Type;

		if (Name == "texture_diffuse")
		{
			SS << DiffuseNr++;
		}
		else if (Name == "texture_specular")
		{
			SS << SpecularNr++;
		}

		Number = SS.str();

		gl::Uniform1i(gl::GetUniformLocation(IShaderProgram, (Name + Number).c_str()), i);
		gl::BindTexture(gl::TEXTURE_2D, Textures[i].ID);
	}
	
	gl::Uniform1f(gl::GetUniformLocation(IShaderProgram, "material.shininess"), 16.0f);

	gl::BindVertexArray(VAO);
	gl::DrawElements(gl::TRIANGLES, Indices.size(), gl::UNSIGNED_INT, 0);
	gl::BindVertexArray(0);

	for (GLuint i = 0; i < Textures.size(); i++)
	{
		gl::ActiveTexture(gl::TEXTURE0 + i);
		gl::BindTexture(gl::TEXTURE_2D, 0);
	}

}

void Mesh::SetUpMesh()
{
	VBO = 0;
	VAO = 0;

	gl::GenVertexArrays(1, &VAO);																					//!< Generate the evertext array for the VAO.
	gl::GenBuffers(1, &VBO);																						//!< Generate buffers for VBO.
	gl::GenBuffers(1, &EBO);

	gl::BindVertexArray(VAO);																						//!< Bind the VAO.

	gl::BindBuffer(gl::ARRAY_BUFFER, VBO);																			//!< Bind the buffers for the VBO.
	gl::BufferData(gl::ARRAY_BUFFER, (Indices.size() * sizeof(Vertex)), &Vertices[0], gl::STATIC_DRAW);				//!< Buffer the triangle points in the VBO.

	gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, EBO);
	gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, (Indices.size() * sizeof(GLuint)), &Indices[0], gl::STATIC_DRAW);
																													//!< Create a vertex array object.
	gl::EnableVertexAttribArray(0);																					//!< Enable the VAO.
	gl::VertexAttribPointer(0, 3, gl::FLOAT, FALSE, sizeof(Vertex), (GLvoid * )0);

	gl::EnableVertexAttribArray(1);																					//!<
	gl::VertexAttribPointer(1, 3, gl::FLOAT, FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, Normal));

	gl::EnableVertexAttribArray(2);																					//!<
	gl::VertexAttribPointer(2, 2, gl::FLOAT, FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, TextureCoords));

	gl::BindVertexArray(0);
}