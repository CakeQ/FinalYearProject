#include <Model.h>

#include <string>
#include <iostream>
#include <vector>

#include <glad/glad.h>

Model::Model(std::string s_IPath)
{
	LoadModel(s_IPath);
}

void Model::LoadModel(std::string s_IPath)
{
	Assimp::Importer ModelImporter;
	const aiScene* Scene = ModelImporter.ReadFile(s_IPath, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!Scene || Scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !Scene->mRootNode)
	{
		std::cout << "ERROR: " << ModelImporter.GetErrorString() << std::endl;
		return;
	}

	s_Directory = s_IPath.substr(0, s_IPath.find_last_of('/'));

	ProcessNode(Scene->mRootNode, Scene);
}

void Model::ProcessNode(aiNode * n_INode, const aiScene * s_IScene)
{
	for (unsigned int i = 0; i < n_INode->mNumMeshes; i++)
	{
		int i_SceneMeshIndex = n_INode->mMeshes[i];
		aiMesh* m_Mesh = s_IScene->mMeshes[i_SceneMeshIndex];
		vt_Meshes.push_back(ProcessMesh(m_Mesh, s_IScene));
	}

	for (unsigned int i = 0; i < n_INode->mNumChildren; i++)
	{
		ProcessNode(n_INode->mChildren[i], s_IScene);
	}
}

Mesh Model::ProcessMesh(aiMesh* m_IMesh, const aiScene* s_IScene)
{
	std::vector<Vertex> vt_NewVertices;
	std::vector<unsigned int> vt_NewIndices;
	std::vector<Texture> vt_NewTextures;

	vt_NewVertices.resize(m_IMesh->mNumVertices);
	vt_NewIndices.resize(m_IMesh->mNumFaces*3);

	for (unsigned int i = 0; i < m_IMesh->mNumVertices; i++)
	{
		vt_NewVertices[i].v3_Position = glm::vec3(m_IMesh->mVertices[i].x, m_IMesh->mVertices[i].y, m_IMesh->mVertices[i].z);
		vt_NewVertices[i].v3_Normal = glm::vec3(m_IMesh->mNormals[i].x, m_IMesh->mNormals[i].y, m_IMesh->mNormals[i].z);

		if (m_IMesh->mTextureCoords[0])
		{
			vt_NewVertices[i].v2_TextureCoords = glm::vec2(m_IMesh->mTextureCoords[0][i].x, m_IMesh->mTextureCoords[0][i].y);
		}
		else
		{
			vt_NewVertices[i].v2_TextureCoords = glm::vec2(0.0f, 0.0f);
		}
	}

	for (unsigned int i = 0; i < m_IMesh->mNumFaces; i++)
	{
		aiFace Face = m_IMesh->mFaces[i];
		for (unsigned int j = 0; j < Face.mNumIndices; j++)
		{
			vt_NewIndices[3 * i + j] = m_IMesh->mFaces[i].mIndices[j];
		}
	}

	/*if (m_IMesh->mMaterialIndex >= 0)
	{
		aiMaterial* m_Material = s_IScene->mMaterials[m_IMesh->mMaterialIndex];

		std::vector<Texture> vt_DiffuseMaps = LoadMaterialTextures(m_Material, aiTextureType_DIFFUSE, "texture_diffuse");
		std::vector<Texture> vt_SpecularMaps = LoadMaterialTextures(m_Material, aiTextureType_DIFFUSE, "texture_specular");
		std::vector<Texture> vt_NormalMaps = LoadMaterialTextures(m_Material, aiTextureType_NORMALS, "texture_normal");
		std::vector<Texture> vt_HeightMaps = LoadMaterialTextures(m_Material, aiTextureType_HEIGHT, "texture_height");
	
		vt_NewTextures.insert(vt_NewTextures.end(), vt_DiffuseMaps.begin(), vt_DiffuseMaps.end());
		vt_NewTextures.insert(vt_NewTextures.end(), vt_SpecularMaps.begin(), vt_SpecularMaps.end());
		vt_NewTextures.insert(vt_NewTextures.end(), vt_NormalMaps.begin(), vt_NormalMaps.end());
		vt_NewTextures.insert(vt_NewTextures.end(), vt_HeightMaps.begin(), vt_HeightMaps.end());
	}*/

	return Mesh(vt_NewVertices, vt_NewIndices, vt_NewTextures);
}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial * m_IMaterial, aiTextureType tt_IType, std::string s_ITypeName)
{
	std::vector<Texture> vt_Textures;

	for (unsigned int i = 0; i < m_IMaterial->GetTextureCount(tt_IType); i++)
	{
		aiString s_TextureString;
		m_IMaterial->GetTexture(tt_IType, i, &s_TextureString);

		bool b_Skip = false;

		for (Texture t_IteratorTexture : vt_Textures)
		{
			if (t_IteratorTexture.s_Path == s_TextureString)
			{
				vt_Textures.push_back(t_IteratorTexture);
				b_Skip = true;
				break;
			}
		}

		if (!b_Skip)
		{
			Texture t_InputTexture;
			t_InputTexture.ui_ID = TextureFromFile(s_TextureString.C_Str(), s_Directory);
			t_InputTexture.s_Type = s_ITypeName;
			t_InputTexture.s_Path = s_TextureString;
			vt_Textures.push_back(t_InputTexture);
			vt_TexturesLoaded.push_back(t_InputTexture);
		}

	}
	return vt_Textures;
}

GLint Model::TextureFromFile(const char * c_IPath, std::string s_IDirectory)
{
	std::string s_FileName = std::string(c_IPath);
	s_FileName = s_FileName.substr(s_FileName.find_last_of('/') + 1, s_FileName.length());
	s_FileName = s_IDirectory + '/' + s_FileName;

	unsigned int ui_TextureID;
	glGenTextures(1, &ui_TextureID);

	int i_Width;
	int i_Height;
	int i_NumComponents;

	unsigned char* uc_Image = SOIL_load_image(s_FileName.c_str(), &i_Width, &i_Height, &i_NumComponents, 0);
	if (uc_Image)
	{
		GLenum n_Format;
		if (i_NumComponents == 1)
		{
			n_Format = GL_RED;
		}
		else if (i_NumComponents == 3)
		{
			n_Format = GL_RGB;
		}
		else if (i_NumComponents == 4)
		{
			n_Format = GL_RGBA;
		}

		glBindTexture(GL_TEXTURE_2D, ui_TextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, n_Format, i_Width, i_Height, 0, n_Format, GL_UNSIGNED_BYTE, uc_Image);

		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		SOIL_free_image_data(uc_Image);
	}
	else
	{
		std::cout << "ERROR: Failed to load texture from: " << s_IDirectory << " (" << c_IPath << ")" << std::endl;
		SOIL_free_image_data(uc_Image);
	}
	return ui_TextureID;
}

void Model::Draw(Shader* s_IShader, glm::mat4 m4_IModelMatrix)
{
	for (Mesh m_IteratorMesh : vt_Meshes)
	{
		m_IteratorMesh.Draw(s_IShader, m4_IModelMatrix);
	}
}
