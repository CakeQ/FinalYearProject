#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include <glm/gtc/matrix_transform.hpp>

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TextureCoords;
};

struct Texture
{
	GLuint ID;
	std::string Type;
	std::string path;
};

class Mesh
{
private:
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	void SetUpMesh();

public:
	std::vector<Vertex> Vertices;
	std::vector<GLuint> Indices;
	std::vector<Texture> Textures;

	Mesh(std::vector<Vertex> IVertices, std::vector<GLuint> IIndices, std::vector<Texture> ITextures);
	void Draw(GLuint IShaderProgram);
};
