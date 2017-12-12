#include <stdafx.h>

#include <Scene.h>

Scene::Scene(EngineCore* e_IGameEngine)
{
	e_GameEngine = e_IGameEngine;
}

void Scene::Update()
{
	for (Entity e_IEntity : vt_EntityList)
	{
		e_IEntity.Update();
	}
}

void Scene::Draw()
{
	e_GameEngine->RenderColouredBackground(0.0f, 0.2f, 0.5f);

	e_GameEngine->SetCamera(c_CurrentCamera);

	for (Entity e_IEntity : vt_EntityList)
	{	
		if (e_IEntity.GetComponent<ModelComponent>()) 
		{
			e_GameEngine->DrawModel(e_IEntity.GetComponent<ModelComponent>()->m_Model, e_IEntity.GetComponent<TransformComponent>()->GetModelMatrix());
		}
	}
}