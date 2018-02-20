#include <Scene.h>

Scene::Scene(EngineCore* e_IEngine)
{
	mm_ModelManager = new ModelManager;
	e_EngineCore = e_IEngine;
}

Scene::~Scene()
{
	for (Entity* o_Iterator : vt_EntityList)
	{
		o_Iterator->~Entity();
		vt_EntityList.pop_back();
	}

	c_SceneCamera = nullptr;
	e_EngineCore = nullptr;
	//e_Background->~Entity();
}

void Scene::Update(float f_IDeltaTime)
{
	for (Entity* o_Iterator : vt_EntityList)
	{
		o_Iterator->Update(f_IDeltaTime);
	}
	//glm::vec3 Pos = e_PlayerEntity->GetComponent<TransformComponent>()->v3_Position;
	//std::cout << Pos.x << ", " << Pos.y << ", " << Pos.z << std::endl;
}

void Scene::Draw()
{
	float f_RedValue = 0, f_GreenValue = 0, f_BlueValue = 0;
	/*if (e_Background->GetComponent<RedComponent>())
		f_RedValue = e_Background->GetComponent<RedComponent>()->f_ColourValue;
	if (e_Background->GetComponent<GreenComponent>())
		f_GreenValue = e_Background->GetComponent<GreenComponent>()->f_ColourValue;
	if (e_Background->GetComponent<BlueComponent>())
		f_BlueValue = e_Background->GetComponent<BlueComponent>()->f_ColourValue;*/

	// e.g. pass object details to the engine to render the next frame
	e_EngineCore->RenderColouredBackground(f_RedValue, f_GreenValue, f_BlueValue);

	// update the camera (probably don't need to do this each frame)
	e_EngineCore->SetCamera(c_SceneCamera);

	for (Entity* e_EntityIterator : vt_EntityList)
	{
		if (e_EntityIterator->GetComponent<ModelComponent>() != nullptr)
		{
			for (Texture texture : e_EntityIterator->GetComponent<ModelComponent>()->m_Model->vt_TexturesLoaded)
			{
				gl::BindTexture(gl::TEXTURE_2D, texture.ui_ID);
			}

			if (!e_EntityIterator->GetComponent<ModelComponent>()->b_Hidden)
			{
				e_EngineCore->DrawModel(e_EntityIterator->GetComponent<ModelComponent>()->m_Model, e_EntityIterator->GetComponent<TransformComponent>()->GetModelMatrix());
			}
		}
	}

	/*for (SceneText* t_Iterator : vt_SceneTextList)
	{
		e_EngineCore->RenderText(t_Iterator->s_Text, t_Iterator->v2_ScreenPos.x, t_Iterator->v2_ScreenPos.y, t_Iterator->f_TextSize, t_Iterator->v3_TextColor);
	}*/
}

void Scene::SetCurrentCamera(CameraComponent* c_ICamera)
{
	c_SceneCamera = c_ICamera;
}