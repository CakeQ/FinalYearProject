#pragma once

#include <fstream>
#include <sstream>
#include <map>

#include <glm\gtc\matrix_transform.hpp>
#include <SOIL2\SOIL2.h>
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include <Mesh.h>
#include <Shader.h>

class Model
{
private:
	std::vector<Mesh> Meshes;
	std::string Directory;
	std::vector<Texture> TexturesLoaded;

	void LoadModel(std::string IPath);
	void ProcessNode(aiNode* INode, const aiScene* IScene);
	Mesh ProcessMesh(aiMesh* IMesh, const aiScene* IScene);
	std::vector<Texture> LoadMaterialTextures(aiMaterial* IMaterial, aiTextureType IType, std::string ITypeName);
	GLint TextureFromFile(const char *IPath, std::string IDirectory);

public:

	Model(GLchar* Path);

	void Draw(Shader IShader);
};