#pragma once

#include <vector>

#include <json/json.h>

#include <EngineCoreBase.h>

#include <Entity.h>

#include <Component.h>
#include <CameraComponent.h>
#include <ColourComponent.h>
#include <ModelComponent.h>
#include <TransformComponent.h>

#include <InputHandler.h>
#include <ModelManager.h>

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
	std::vector<Entity*> vt_EntityList;
	Entity* e_Background;

public:
	std::vector<SceneText*> vt_SceneTextList;

	Entity* e_PlayerEntity;
	CameraComponent* c_SceneCamera;
	EngineCore* e_EngineCore;
	InputHandler* ih_InputHandler;
	ModelManager* mm_ModelManager;

	Scene(EngineCore* e_IEngine);
	~Scene();

	void Update();
	void Draw();
	void SetUpScene();
	void SetCurrentCamera(CameraComponent* c_ICamera);
};