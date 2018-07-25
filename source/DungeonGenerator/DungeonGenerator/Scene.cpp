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

void Scene::SortInstancedEntities()
{
	for (Entity* e_IteratorEntity : vt_EntityList)
	{
		if (!e_IteratorEntity->GetComponent<ModelComponent>()) continue;												//!< Check to see if Entity has ModelComponent.
		ModelComponent* c_IteratorModelComponent = e_IteratorEntity->GetComponent<ModelComponent>();
		if (!c_IteratorModelComponent->m_Model || c_IteratorModelComponent->b_Hidden) continue;							//!< Check to see if ModelComponent has Model.
		Model* m_IteratorModel = c_IteratorModelComponent->m_Model;

		bool b_iterated = false;
		for (InstancedEntity* e_InstancedEntity : vt_InstancedEntities)
		{
			if (e_InstancedEntity->m_Model == m_IteratorModel)
			{
				for (Entity* e_OtherEntity : e_InstancedEntity->vt_EntityList)
				{
					if (e_OtherEntity == e_IteratorEntity)
					{
						b_iterated = true;
					}
				}
				if (b_iterated) break;
				else
				{
					e_InstancedEntity->vt_EntityList.push_back(e_IteratorEntity);
					b_iterated = true;
				}
			}
			if (b_iterated) break;
		}

		if (b_iterated) continue;

		std::vector<Entity*> vt_MatchingEntities;

		for (Entity* e_OtherEntity : vt_EntityList)
		{
			if (!e_OtherEntity->GetComponent<ModelComponent>()) continue;												//!< Check to see if Other Entity has ModelComponent.
			ModelComponent* c_OtherModelComponent = e_OtherEntity->GetComponent<ModelComponent>();
			if (!c_OtherModelComponent->m_Model || c_OtherModelComponent->b_Hidden) continue;							//!< Check to see if Other ModelComponent has Model.
			Model* c_OtherModel = c_OtherModelComponent->m_Model;
			if (c_OtherModel != m_IteratorModel) continue;																//!< Check to see if Other Model matches Model.

			vt_MatchingEntities.push_back(e_OtherEntity);
		}

		if (vt_MatchingEntities.size() == 1) continue;

		InstancedEntity* e_NewInstancedEntity = new InstancedEntity;
		e_NewInstancedEntity->m_Model = m_IteratorModel;
		for (Entity* e_MatchingEntity : vt_MatchingEntities)
		{
			e_NewInstancedEntity->vt_EntityList.push_back(e_MatchingEntity);
		}
		vt_InstancedEntities.push_back(e_NewInstancedEntity);
	}
}