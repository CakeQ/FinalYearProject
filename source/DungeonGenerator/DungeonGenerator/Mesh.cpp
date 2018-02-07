#include <Mesh.h>

#include <gl_core_4_3.hpp>

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


void Mesh::Draw(Shader* s_IShader, glm::mat4 m4_IModelMatrix)
{
	// bind the appropriate textures
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;
	for (unsigned int i = 0; i < vt_Textures.size(); i++)
	{
		gl::ActiveTexture(gl::TEXTURE0 + i);

		std::string number;
		std::string name = vt_Textures[i].s_Type;
		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++);
		else if (name == "texture_normal")
			number = std::to_string(normalNr++);
		else if (name == "texture_height")
			number = std::to_string(heightNr++);

		// now set the sampler to the correct texture unit
		gl::Uniform1i(gl::GetUniformLocation(s_IShader->ui_ShaderProgram, (name + number).c_str()), i);
		// and finally bind the texture
		gl::BindTexture(gl::TEXTURE_2D, vt_Textures[i].ui_ID);
	}

	// set the model component of our shader to the object model
	gl::UniformMatrix4fv(gl::GetUniformLocation(s_IShader->ui_ShaderProgram, "model"), 1, gl::FALSE_, glm::value_ptr(m4_IModelMatrix));

	// draw mesh
	gl::BindVertexArray(ui_VAO);
	gl::DrawElements(gl::TRIANGLES, vt_Indices.size(), gl::UNSIGNED_INT, 0);
	gl::BindVertexArray(0);

	// return to default texture
	for (unsigned int i = 0; i < vt_Textures.size(); i++)
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
	gl::VertexAttribPointer(0, 3, gl::FLOAT, false, sizeof(Vertex), (GLvoid * )0);

	gl::EnableVertexAttribArray(1);																						//!< Apply normals.
	gl::VertexAttribPointer(1, 3, gl::FLOAT, false, sizeof(Vertex), (GLvoid *)offsetof(Vertex, v3_Normal));

	gl::EnableVertexAttribArray(2);																						//!< Apply Texture coords.
	gl::VertexAttribPointer(2, 2, gl::FLOAT, false, sizeof(Vertex), (GLvoid *)offsetof(Vertex, v2_TextureCoords));

	gl::BindVertexArray(0);
}
