#pragma once

#include <json\json.h>
#include <SOIL2\SOIL2.h>

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Model.h"

struct Asset
{
	std::string s_ModelName;
	Model* m_Model;
};

class ModelManager
{
public:
	std::vector<Asset*> vt_AssetList;

	~ModelManager()
	{
		for (Asset* a_Iterator : vt_AssetList)
		{
			vt_AssetList.pop_back();
		}
	};

	bool JSONLoadModels(std::string s_IAssetsFile)
	{
		std::fstream JSONData;
		Json::Value JSONRoot;
		Json::Reader JSONReader;

		JSONData.open(s_IAssetsFile.c_str());

		if (!JSONReader.parse(JSONData, JSONRoot))
		{
			std::cout << "ERROR: Failed to parse data from:" << s_IAssetsFile << JSONReader.getFormattedErrorMessages();
			return false;
		}

		std::cout << "Pre-loading models: " << s_IAssetsFile << std::endl;

		const Json::Value v_AssetList = JSONRoot["Assets"];

		for (unsigned int i = 0; i < v_AssetList.size(); i++)
		{
			Asset* a_NewAsset = new Asset;

			for (Asset* a_IteratorAsset : vt_AssetList)
			{
				if (v_AssetList[i]["name"].asString() == a_IteratorAsset->s_ModelName)
				{
					std::cout << "ERROR: " << v_AssetList[i]["name"].asString() << " asset is already defined\n";
				}
			}

			a_NewAsset->s_ModelName = v_AssetList[i]["name"].asString();
			std::cout << v_AssetList[i]["name"].asString() << " asset pre-loaded\n";

			const Json::Value v_ModelDirectory = v_AssetList[i]["model"];

			if (v_ModelDirectory.type() == Json::nullValue)
			{
				std::cout << v_AssetList[i]["name"].asString() << " asset has no model defined\n";
			}
			else
			{
				a_NewAsset->m_Model = new Model(v_ModelDirectory.asString());

				for (unsigned int i = 0; i < a_NewAsset->m_Model->vt_Meshes.size(); i++)
				{
					a_NewAsset->m_Model->vt_Meshes[i].vt_Textures.clear();
				}

				const Json::Value v_DiffuseDirectory = v_AssetList[i]["texture_diffuse"];
				if (v_DiffuseDirectory.type() == Json::nullValue)
				{
					std::cout << v_AssetList[i]["name"].asString() << " asset has no texture defined\n";
				}
				else
				{
					for (unsigned int i = 0; i < v_DiffuseDirectory.size(); i++)
					{
						Texture t_NewTexture;
						t_NewTexture.ui_ID = TextureFromFile(v_DiffuseDirectory[i].asString());
						t_NewTexture.s_Type = "texture_diffuse";
						t_NewTexture.s_Path = v_DiffuseDirectory[i].asString();
						a_NewAsset->m_Model->vt_Meshes[i].vt_Textures.push_back(t_NewTexture);
					}
				}

				const Json::Value v_SpecularDirectory = v_AssetList[i]["texture_diffuse"];
				if (v_SpecularDirectory.type() != Json::nullValue)
				{
					for (unsigned int i = 0; i < v_SpecularDirectory.size(); i++)
					{
						Texture t_NewTexture;
						t_NewTexture.ui_ID = TextureFromFile(v_SpecularDirectory[i].asString());
						t_NewTexture.s_Type = "texture_specular";
						t_NewTexture.s_Path = v_SpecularDirectory[i].asString();
						a_NewAsset->m_Model->vt_Meshes[i].vt_Textures.push_back(t_NewTexture);
					}
				}

				const Json::Value v_NormalDirectory = v_AssetList[i]["texture_diffuse"];
				if (v_NormalDirectory.type() != Json::nullValue)
				{
					for (unsigned int i = 0; i < v_NormalDirectory.size(); i++)
					{
						Texture t_NewTexture;
						t_NewTexture.ui_ID = TextureFromFile(v_NormalDirectory[i].asString());
						t_NewTexture.s_Type = "texture_normal";
						t_NewTexture.s_Path = v_NormalDirectory[i].asString();
						a_NewAsset->m_Model->vt_Meshes[i].vt_Textures.push_back(t_NewTexture);
					}
				}

				const Json::Value v_HeightDirectory = v_AssetList[i]["texture_diffuse"];
				if (v_HeightDirectory.type() != Json::nullValue)
				{
					for (unsigned int i = 0; i < v_HeightDirectory.size(); i++)
					{
						Texture t_NewTexture;
						t_NewTexture.ui_ID = TextureFromFile(v_HeightDirectory[i].asString());
						t_NewTexture.s_Type = "texture_height";
						t_NewTexture.s_Path = v_HeightDirectory[i].asString();
						a_NewAsset->m_Model->vt_Meshes[i].vt_Textures.push_back(t_NewTexture);
					}
				}
				vt_AssetList.push_back(a_NewAsset);
			}
		}
		return true;
	};

	// static function to load a texture using lightweight stb_image library
	GLint TextureFromFile(const std::string s_IDirectory)
	{
		unsigned int ui_TextureID;
		glGenTextures(1, &ui_TextureID);

		int i_Width;
		int i_Height;
		int i_NumComponents;

		unsigned char* uc_Image = SOIL_load_image(s_IDirectory.c_str(), &i_Width, &i_Height, &i_NumComponents, 0);
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
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			}

			glBindTexture(GL_TEXTURE_2D, ui_TextureID);
			glTexImage2D(GL_TEXTURE_2D, 0, n_Format, i_Width, i_Height, 0, n_Format, GL_UNSIGNED_BYTE, uc_Image);

			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			SOIL_free_image_data(uc_Image);
		}
		else
		{
			std::cout << "ERROR: Failed to load texture from: " << s_IDirectory << std::endl;
			SOIL_free_image_data(uc_Image);
		}
		return ui_TextureID;
	}
};