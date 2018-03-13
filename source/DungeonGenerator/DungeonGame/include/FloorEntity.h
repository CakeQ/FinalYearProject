#pragma once

#include <StaticEntity.h>

class FloorEntity : public StaticEntity
{
public:
	int i_State = 0;
	ModelManager* mm_ModelManager;

	FloorEntity(ModelManager* mm_IModelManager)
	{
		mm_ModelManager = mm_IModelManager;
		i_State = rand() % 7;
		ChangeState();
	}

	void ChangeState()
	{
		std::string s_Variation;

		switch (i_State)
		{
		case 0:
			s_Variation = "floor_s_a";
			break;
		case 1:
			s_Variation = "floor_s_b";
			break;
		case 2:
			s_Variation = "floor_s_c";
			break;
		case 3:
			s_Variation = "floor_s_d";
			break;
		case 4:
			s_Variation = "floor_s_e";
			break;
		case 5:
			s_Variation = "floor_s_f";
			break;
		case 6:
			s_Variation = "floor_s_g";
			break;
		default:
			s_Variation = "floor_s_a";
			break;
		}

		for (Asset* a_IteratorAsset : mm_ModelManager->vt_AssetList)
		{
			if (s_Variation == a_IteratorAsset->s_ModelName)
			{
				GetComponent<ModelComponent>()->m_Model = a_IteratorAsset->m_Model;
				continue;
			}
		}

		GetComponent<TransformComponent>()->Pitch(glm::radians(90.0f));
	}

	void Update(float f_IDeltaTime) override
	{

	}

	void Message(const std::string s_IMessage) override
	{

	}
};