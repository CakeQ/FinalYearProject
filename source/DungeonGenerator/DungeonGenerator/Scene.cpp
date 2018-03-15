#include <Scene.h>

Scene::Scene(EngineCore* e_IEngine)
{
	mm_ModelManager = new ModelManager;
	e_GameEngine = e_IEngine;
}

Scene::~Scene()
{
	for (Entity* o_Iterator : vt_EntityList)
	{
		o_Iterator->~Entity();
		vt_EntityList.pop_back();
	}

	c_SceneCamera = nullptr;
	e_GameEngine = nullptr;
	//e_Background->~Entity();

	for (b2Body* b2_BodyIterator = b2_World->GetBodyList(); b2_BodyIterator != 0; b2_BodyIterator = b2_BodyIterator->GetNext())
	{
		if (b2_BodyIterator)
		{
			b2_World->DestroyBody(b2_BodyIterator);
		}
	}
}

void Scene::SetCurrentCamera(CameraComponent* c_ICamera)
{
	c_SceneCamera = c_ICamera;
}