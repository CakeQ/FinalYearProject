#include <stdafx.h>

#include <Model.h>

void Model::LoadModel(std::string IPath)
{
	Assimp::Importer ModelImporter;
	const aiScene* Scene = ModelImporter.ReadFile(IPath, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!Scene || Scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !Scene->mRootNode)
	{
		std::cout << "ERROR: " << ModelImporter.GetErrorString() << std::endl;
		return;
	}

	Directory = IPath.substr(0, IPath.find_last_of('/'));

	ProcessNode(Scene->mRootNode, Scene);
}

void Model::ProcessNode(aiNode * INode, const aiScene * IScene)
{
	for (GLuint i = 0; i < INode->mNumMeshes; i++)
	{
		aiMesh* Mesh = IScene->mMeshes[INode->mMeshes[i]];

		Meshes.push_back(ProcessMesh(Mesh, IScene));
	}

	for (GLuint i = 0; i < INode->mNumChildren; i++)
	{
		ProcessNode(INode->mChildren[i], IScene);
	}
}

Mesh Model::ProcessMesh(aiMesh* IMesh, const aiScene* IScene)
{
	std::vector<Vertex> Vertices;
	std::vector<GLuint> Indices;
	std::vector<Texture> Textures;

	for (GLuint i = 0; i < IMesh->mNumVertices; i++)
	{
		Vertex InputVertex;
		glm::vec3 Vector;

		Vector.x = IMesh->mVertices[i].x;
		Vector.y = IMesh->mVertices[i].y;
		Vector.z = IMesh->mVertices[i].z;
		InputVertex.Position = Vector;
		
		Vector.x = IMesh->mNormals[i].x;
		Vector.y = IMesh->mNormals[i].y;
		Vector.z = IMesh->mNormals[i].z;
		InputVertex.Normal = Vector;

		if (IMesh->mTextureCoords[0])
		{
			glm::vec2 TextureVector;

			TextureVector.x = IMesh->mTextureCoords[0][i].x;
			TextureVector.y = IMesh->mTextureCoords[0][i].y;
			InputVertex.TextureCoords = TextureVector;
		}
		else
		{
			InputVertex.TextureCoords = glm::vec2(0.0f, 0.0f);
		}

		Vertices.push_back(InputVertex);
	}

	for (GLuint i = 0; i < IMesh->mNumFaces; i++)
	{
		aiFace Face = IMesh->mFaces[i];
		for (GLuint j = 0; j < Face.mNumIndices; j++)
		{
			Indices.push_back(Face.mIndices[j]);
		}
	}

	if (IMesh->mMaterialIndex >= 0)
	{
		aiMaterial* Material = IScene->mMaterials[IMesh->mMaterialIndex];

		std::vector<Texture> DiffuseMaps = LoadMaterialTextures(Material, aiTextureType_DIFFUSE, "texture_diffuse");
		Textures.insert(Textures.end(), DiffuseMaps.begin(), DiffuseMaps.end());

		std::vector<Texture> SpecularMaps = LoadMaterialTextures(Material, aiTextureType_DIFFUSE, "texture_specular");
		Textures.insert(Textures.end(), SpecularMaps.begin(), SpecularMaps.end());
	}

	return Mesh(Vertices, Indices, Textures);
}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial * IMaterial, aiTextureType IType, std::string ITypeName)
{
	std::vector<Texture> Textures;

	for (GLuint i = 0; i < IMaterial->GetTextureCount(IType); i++)
	{
		aiString TextureString;
		IMaterial->GetTexture(IType, i, &TextureString);

		GLboolean Skip = false;

		for (GLuint j = 0; j < TexturesLoaded.size(); j++)
		{
			if (TexturesLoaded[j].Path == TextureString)
			{
				Textures.push_back(TexturesLoaded[j]);
				Skip = true;

				break;
			}
		}

		if (!Skip)
		{
			Texture InputTexture;
			InputTexture.ID = TextureFromFile(TextureString.C_Str(), Directory);
			InputTexture.Type = ITypeName;
			InputTexture.Path = TextureString;
			Textures.push_back(InputTexture);

			TexturesLoaded.push_back(InputTexture);
		}

	}
	return Textures;
}

GLint Model::TextureFromFile(const char * IPath, std::string IDirectory)
{
	std::string FileName = std::string(IPath);
	FileName = IDirectory + '/' + FileName;
	GLuint TextureID;
	gl::GenTextures(1, &TextureID);

	int Width;
	int Height;

	unsigned char* Image = SOIL_load_image(FileName.c_str(), &Width, &Height, 0, SOIL_LOAD_RGB);

	gl::BindTexture(gl::TEXTURE_2D, TextureID);
	gl::TexImage2D(gl::TEXTURE_2D, 0, gl::RGB, Width, Height, 0, gl::RGB, gl::UNSIGNED_BYTE, Image);

	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_S, gl::REPEAT);
	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_T, gl::REPEAT);
	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::LINEAR_MIPMAP_LINEAR);
	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::LINEAR);
	gl::BindTexture(gl::TEXTURE_2D, 0);
	SOIL_free_image_data(Image);

	return TextureID;
}

Model::Model(GLchar * Path)
{
	LoadModel(Path);
}

void Model::Draw(Shader IShader)
{
	for (GLuint i = 0; i < Meshes.size(); i++)
	{
		std::cout << "Model drawing" << std::endl;
		Meshes[i].Draw(IShader);
		std::cout << Meshes.size() << std::endl;
	}
}
