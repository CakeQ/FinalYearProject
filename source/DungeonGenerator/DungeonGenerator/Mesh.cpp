#include <Mesh.h>

#include <glad/glad.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

Mesh::Mesh(std::vector<Vertex> vt_IVertices, std::vector<GLuint> vt_IIndices, std::vector<Texture> vt_ITextures)
{
	vt_Vertices = vt_IVertices;
	vt_Indices = vt_IIndices;
	vt_Textures = vt_ITextures;

	SetUpMesh();
}


void Mesh::Draw(Shader* s_IShader, glm::mat4* m4_IModelMatrix)
{
	// bind the appropriate textures
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;
	for (unsigned int i = 0; i < vt_Textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);

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
		glUniform1i(glGetUniformLocation(s_IShader->ui_ShaderProgram, (name + number).c_str()), i);
		// and finally bind the texture
		glBindTexture(GL_TEXTURE_2D, vt_Textures[i].ui_ID);
	}

	// draw mesh
	glBindVertexArray(ui_VAO);
	glDrawElementsInstanced(GL_TRIANGLES, vt_Indices.size(), GL_UNSIGNED_INT, 0, m4_IModelMatrix->length());
	glBindVertexArray(0);

	// return to default texture
	for (unsigned int i = 0; i < vt_Textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}


void Mesh::SetUpMesh()
{
	glGenVertexArrays(1, &ui_VAO);																					//!< Generate the evertext array for the VAO.
	glGenBuffers(1, &ui_VBO);																						//!< Generate buffers for VBO.
	glGenBuffers(1, &ui_EBO);

	glBindVertexArray(ui_VAO);																						//!< Bind the VAO.

	glBindBuffer(GL_ARRAY_BUFFER, ui_VBO);																			//!< Bind the buffers for the VBO.
	glBufferData(GL_ARRAY_BUFFER, (vt_Indices.size() * sizeof(Vertex)), &vt_Vertices[0], GL_STATIC_DRAW);			//!< Buffer the triangle points in the VBO.

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ui_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (vt_Indices.size() * sizeof(GLuint)), &vt_Indices[0], GL_STATIC_DRAW);
																													//!< Create a vertex array object.
	glEnableVertexAttribArray(0);																					//!< Enable the VAO.
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), (GLvoid * )0);

	glEnableVertexAttribArray(1);																					//!< Apply normals.
	glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(Vertex), (GLvoid *)offsetof(Vertex, v3_Normal));

	glEnableVertexAttribArray(2);																					//!< Apply Texture coords.
	glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(Vertex), (GLvoid *)offsetof(Vertex, v2_TextureCoords));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, false, sizeof(glm::mat4), (GLvoid *)0);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, false, sizeof(glm::mat4), (GLvoid *)(sizeof(glm::vec4)));
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, false, sizeof(glm::mat4), (GLvoid *)(2 * sizeof(glm::vec4)));
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, false, sizeof(glm::mat4), (GLvoid*)(3 * sizeof(glm::vec4)));

	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);
	glVertexAttribDivisor(6, 1);

	glBindVertexArray(0);
}
