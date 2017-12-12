/**
* \file Game.h
*/

//! Game controller class.
/*!
Game controller used to handle everything game related.
Created by Daniel Thompson, P15230940.
*/

#pragma once

#include <EngineCoreBase.h>
#include <Entity.h>
#include <Component.h>
#include <ModelComponent.h>
#include <CameraComponent.h>
#include <MovementComponent.h>
#include <Shader.h>
#include <Scene.h>

class Game
{
private:

public:
	EngineCore* g_GameEngine;
	Scene* s_CurrentScene;

	Game();

	void HandleInput(const std::vector<bool>& vt_IKeyBuffer, const glm::vec2 v2_IMousebuffer);
	void Update();
	void Draw();

	void SetUpTestScene();
};