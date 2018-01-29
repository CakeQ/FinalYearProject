#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <map>

#include <gl_core_4_3.hpp>
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
	std::string s_Directory;

	void LoadModel(std::string s_IPath);
	void ProcessNode(aiNode* n_INode, const aiScene* s_IScene);
	Mesh ProcessMesh(aiMesh* m_IMesh, const aiScene* s_IScene);
	std::vector<Texture> LoadMaterialTextures(aiMaterial* m_IMaterial, aiTextureType t_IType, std::string s_ITypeName);

public:
	std::vector<Texture> vt_TexturesLoaded;
	std::vector<Mesh> vt_Meshes;

	Model(std::string filepath);
	void Draw(Shader* s_IShader);
	GLint TextureFromFile(const char *c_IPath, std::string s_IDirectory);
};