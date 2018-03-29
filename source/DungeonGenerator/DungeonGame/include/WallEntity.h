#pragma once

#include "DungeonEntity.h"
#include "ModelManager.h"

class WallEntity : public DungeonEntity
{

public:
	int i_State = 0;
	ModelManager* mm_ModelManager;

	WallEntity(ModelManager* mm_IModelManager)
	{
		mm_ModelManager = mm_IModelManager;
		ChangeState();
	}

	void CalculateState() override
	{

	}

	void ChangeState() override //You need to change this to work with neighbor system
	{
		std::string s_Variation;
		float f_Rotation = 0.0f;

		if (i_State == 0 || i_State == 1 || i_State == 2 || i_State == 4 || i_State == 8)
		{
			s_Variation = "wall_m";
		}
		else if (i_State == 5 || i_State == 10)
		{
			switch (rand() % 3)
			{
			case 0:
				s_Variation = "wall_s_a";
				break;
			case 1:
				s_Variation = "wall_s_b";
				break;
			case 2:
				s_Variation = "wall_s_c";
				break;
			default:
				s_Variation = "wall_s_a";
				break;
			}
			if (i_State == 10)
			{
				f_Rotation = 90.0f;
			}
		}
		else if (i_State == 7 || i_State == 11 || i_State == 13 || i_State == 14)
		{
			s_Variation = "wall_t";

			switch (i_State)
			{
			case 7:
				f_Rotation = 90.0f;
				break;
			case 11:
				f_Rotation = 0.0f;
				break;
			case 13:
				f_Rotation = 270.0f;
				break;
			case 14:
				f_Rotation = 180.0f;
				break;
			default:
				break;
			}
		}
		else if (i_State == 3 || i_State == 6 || i_State == 9 || i_State == 12)
		{
			s_Variation = "wall_c";

			switch (i_State)
			{
			case 3:
				f_Rotation = 0.0f;
				break;
			case 6:
				f_Rotation = 90.0f;
				break;
			case 9:
				f_Rotation = 270.0f;
				break;
			case 12:
				f_Rotation = 180.0f;
				break;
			default:
				break;
			}
		}
		else
		{
			s_Variation = "wall_i";
		}

		for (Asset* a_IteratorAsset : mm_ModelManager->vt_AssetList)
		{
			if (s_Variation == a_IteratorAsset->s_ModelName)
			{
				GetComponent<ModelComponent>()->m_Model = a_IteratorAsset->m_Model;
				continue;
			}
		}

		GetComponent<TransformComponent>()->Roll(glm::radians(f_Rotation));
	}
};