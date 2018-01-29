#include <Scene.h>

#include <fstream>
#include <sstream>

#include "Model.h"

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
	e_Background->~Entity();
}

void Scene::Update()
{
	for (Entity* o_Iterator : vt_EntityList)
	{
		o_Iterator->Update();
	}
}

void Scene::Draw()
{
	float f_RedValue = 0, f_GreenValue = 0, f_BlueValue = 0;
	if (e_Background->GetComponent<RedComponent>())
		f_RedValue = e_Background->GetComponent<RedComponent>()->f_ColourValue;
	if (e_Background->GetComponent<GreenComponent>())
		f_GreenValue = e_Background->GetComponent<GreenComponent>()->f_ColourValue;
	if (e_Background->GetComponent<BlueComponent>())
		f_BlueValue = e_Background->GetComponent<BlueComponent>()->f_ColourValue;

	// e.g. pass object details to the engine to render the next frame
	e_EngineCore->RenderColouredBackground(f_RedValue, f_GreenValue, f_BlueValue);

	// update the camera (probably don't need to do this each frame)
	e_EngineCore->SetCamera(c_SceneCamera);

	for (Entity* e_EntityIterator : vt_EntityList)
	{
		if (e_EntityIterator->GetComponent<ModelComponent>())
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

void Scene::SetUpScene()
{
	Model* m_NewModel = new Model("assets/meshes/walls/Wall.obj");

	Entity* e_TestModel = new Entity();
	Entity* e_Player = new Entity();

	ModelComponent* c_ModelComponent = new ModelComponent;
	c_ModelComponent->m_Model = m_NewModel;

	TransformComponent* c_TransformComponent = new TransformComponent;
	c_TransformComponent->v3_Position = glm::vec3(0.0f, -8.0f, -25.0f);
	c_TransformComponent->q_Orientation = glm::quat(0.0f, 0.0f, 0.0f, 0.0f);
	c_TransformComponent->v3_Scale = glm::vec3(1.0f, 1.0f, 1.0f);

	e_TestModel->AddComponent(c_ModelComponent);
	e_TestModel->AddComponent(c_TransformComponent);

	CameraComponent* c_CameraComponent = new CameraComponent;

	TransformComponent* c_TransformComponent2 = new TransformComponent;
	c_TransformComponent2->v3_Position = glm::vec3(0.0f, 0.0f, 4.0f);
	c_TransformComponent2->q_Orientation = glm::quat(0.0f, 0.0f, 0.0f, 0.0f);
	c_TransformComponent2->v3_Scale = glm::vec3(1.0f, 1.0f, 1.0f);

	e_Player->AddComponent(c_CameraComponent);
	e_Player->AddComponent(c_TransformComponent2);

	vt_EntityList.push_back(e_TestModel);
	vt_EntityList.push_back(e_Player);
	SetCurrentCamera(c_CameraComponent);
};