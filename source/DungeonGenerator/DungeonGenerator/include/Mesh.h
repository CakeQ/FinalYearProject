#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Shader.h"

struct Vertex
{
	glm::vec3 v3_Position;
	glm::vec3 v3_Normal;
	glm::vec2 v2_TextureCoords;
};

struct Texture
{
	GLuint ui_ID;
	std::string s_Type;
	aiString s_Path;
};

class Mesh
{
private:
	GLuint ui_VBO;
	GLuint ui_EBO;

	void SetUpMesh();

public:
	GLuint ui_VAO;
	std::vector<Vertex> vt_Vertices;
	std::vector<GLuint> vt_Indices;
	std::vector<Texture> vt_Textures;

	Mesh(std::vector<Vertex> vt_IVertices, std::vector<GLuint> vt_IIndices, std::vector<Texture> vt_ITextures);
	void Draw(Shader* s_IShader, glm::mat4 m4_IModelMatrix);
};
