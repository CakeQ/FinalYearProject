#pragma once

#include <vector>
#include <fstream>
#include <sstream>

#include <json/json.h>

#include "EngineCoreBase.h"

#include "Component.h"
#include "CameraComponent.h"
#include "ColourComponent.h"
#include "ModelComponent.h"
#include "TransformComponent.h"

#include "InputHandler.h"
#include "ModelManager.h"

#include "Model.h"
#include "Entity.h"
#include "StaticEntity.h"
#include "PlayerEntity.h"


struct SceneText
{
	glm::vec3 v3_TextColor;
	glm::vec2 v2_ScreenPos;
	std::string s_Text;
	std::string s_Font;
	float f_TextSize;
};

class Scene
{
private:
	EngineCore* e_GameEngine;

public:
	std::vector<Entity*> vt_EntityList;
	std::vector<SceneText*> vt_SceneTextList;

	Entity* e_PlayerEntity;
	CameraComponent* c_SceneCamera;
	
	InputHandler* ih_InputHandler;
	ModelManager* mm_ModelManager;

	Scene(EngineCore* e_IEngine);
	~Scene();

	void Update(float f_IDeltaTime);
	void Draw();
	virtual void SetUpScene() = 0;
	void SetCurrentCamera(CameraComponent* c_ICamera);
};