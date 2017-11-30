#include <stdafx.h>

#include <Model.h>

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
	for (GLuint i = 0; i < n_INode->mNumMeshes; i++)
	{
		aiMesh* m_Mesh = s_IScene->mMeshes[n_INode->mMeshes[i]];

		vt_Meshes.push_back(ProcessMesh(m_Mesh, s_IScene));
	}

	for (GLuint i = 0; i < n_INode->mNumChildren; i++)
	{
		ProcessNode(n_INode->mChildren[i], s_IScene);
	}
}

Mesh Model::ProcessMesh(aiMesh* m_IMesh, const aiScene* s_IScene)
{
	std::vector<Vertex> vt_Vertices;
	std::vector<GLuint> vt_Indices;
	std::vector<Texture> vt_Textures;

	vt_Vertices.resize(m_IMesh->mNumVertices);
	vt_Indices.resize(m_IMesh->mNumFaces*3);

	for (GLuint i = 0; i < m_IMesh->mNumVertices; i++)
	{
		Vertex v_InputVertex;
		glm::vec3 v3_Vector;

		v3_Vector.x = m_IMesh->mVertices[i].x;
		v3_Vector.y = m_IMesh->mVertices[i].y;
		v3_Vector.z = m_IMesh->mVertices[i].z;
		v_InputVertex.v3_Position = v3_Vector;
		
		if (m_IMesh->mNormals[i].x)
		{
			v3_Vector.x = m_IMesh->mNormals[i].x;
			v3_Vector.y = m_IMesh->mNormals[i].y;
			v3_Vector.z = m_IMesh->mNormals[i].z;
			v_InputVertex.v3_Normal = v3_Vector;
		}
		else
		{
			v_InputVertex.v3_Normal = glm::vec3(0.0f, 0.0f, 0.0f);
		}

		if (m_IMesh->mTextureCoords[0])
		{
			glm::vec2 v2_TextureVector;

			v2_TextureVector.x = m_IMesh->mTextureCoords[0][i].x;
			v2_TextureVector.y = m_IMesh->mTextureCoords[0][i].y;
			v_InputVertex.v2_TextureCoords = v2_TextureVector;
		}
		else
		{
			v_InputVertex.v2_TextureCoords = glm::vec2(0.0f, 0.0f);
		}

		vt_Vertices[i] = v_InputVertex;
	}

	for (GLuint i = 0; i < m_IMesh->mNumFaces; i++)
	{
		aiFace Face = m_IMesh->mFaces[i];
		for (GLuint j = 0; j < Face.mNumIndices; j++)
		{
			vt_Indices[3 * i + j] = m_IMesh->mFaces[i].mIndices[j];
		}
	}

	if (m_IMesh->mMaterialIndex >= 0)
	{
		aiMaterial* m_Material = s_IScene->mMaterials[m_IMesh->mMaterialIndex];

		std::vector<Texture> vt_DiffuseMaps = LoadMaterialTextures(m_Material, aiTextureType_DIFFUSE, "texture_diffuse");
		vt_Textures.insert(vt_Textures.end(), vt_DiffuseMaps.begin(), vt_DiffuseMaps.end());

		std::vector<Texture> vt_SpecularMaps = LoadMaterialTextures(m_Material, aiTextureType_DIFFUSE, "texture_specular");
		vt_Textures.insert(vt_Textures.end(), vt_SpecularMaps.begin(), vt_SpecularMaps.end());

		std::vector<Texture> vt_NormalMaps = LoadMaterialTextures(m_Material, aiTextureType_NORMALS, "texture_normal");

		std::vector<Texture> vt_HeightMaps = LoadMaterialTextures(m_Material, aiTextureType_HEIGHT, "texture_height");
	
		vt_Textures.insert(vt_Textures.end(), vt_DiffuseMaps.begin(), vt_DiffuseMaps.end());
		vt_Textures.insert(vt_Textures.end(), vt_SpecularMaps.begin(), vt_SpecularMaps.end());
		vt_Textures.insert(vt_Textures.end(), vt_NormalMaps.begin(), vt_NormalMaps.end());
		vt_Textures.insert(vt_Textures.end(), vt_HeightMaps.begin(), vt_HeightMaps.end());
	}

	return Mesh(vt_Vertices, vt_Indices, vt_Textures);
}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial * m_IMaterial, aiTextureType tt_IType, std::string s_ITypeName)
{
	std::vector<Texture> vt_Textures;

	for (GLuint i = 0; i < m_IMaterial->GetTextureCount(tt_IType); i++)
	{
		aiString s_TextureString;
		m_IMaterial->GetTexture(tt_IType, i, &s_TextureString);

		GLboolean Skip = false;

		for (Texture t_IteratorTexture : vt_Textures)
		{
			if (t_IteratorTexture.s_Path == s_TextureString)
			{
				vt_Textures.push_back(t_IteratorTexture);
				Skip = true;

				break;
			}
		}

		if (!Skip)
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
	s_FileName = s_IDirectory + '/' + s_FileName;
	GLuint ui_TextureID;
	gl::GenTextures(1, &ui_TextureID);

	int i_Width;
	int i_Height;
	int i_NumComponents;

	unsigned char* uc_Image = SOIL_load_image(s_FileName.c_str(), &i_Width, &i_Height, &i_NumComponents, 0);
	if (uc_Image)
	{
		GLenum n_Format;
		if (i_NumComponents == 1)
		{
			n_Format = gl::RED;
		}
		else if (i_NumComponents == 3)
		{
			n_Format = gl::RGB;
		}
		else if (i_NumComponents == 4)
		{
			n_Format = gl::RGBA;
		}

		gl::BindTexture(gl::TEXTURE_2D, ui_TextureID);
		gl::TexImage2D(gl::TEXTURE_2D, 0, n_Format, i_Width, i_Height, 0, n_Format, gl::UNSIGNED_BYTE, uc_Image);

		gl::GenerateMipmap(gl::TEXTURE_2D);

		gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_S, gl::REPEAT);
		gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_T, gl::REPEAT);
		gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::LINEAR_MIPMAP_LINEAR);
		gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::LINEAR);

		SOIL_free_image_data(uc_Image);
	}
	else
	{
		std::cout << "ERROR: Failed to load texture from: " << s_IDirectory << std::endl;
		SOIL_free_image_data(uc_Image);
	}
	return ui_TextureID;
}

Model::Model(GLchar * c_Path)
{
	LoadModel(c_Path);
}

void Model::Draw(Shader* s_IShader)
{
	for (Mesh m_IteratorMesh : vt_Meshes)
	{
		m_IteratorMesh.Draw(s_IShader);
	}
}
