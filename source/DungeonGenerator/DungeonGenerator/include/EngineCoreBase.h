/**
* \file EngineCoreBase.h
*/

//! Parent engine core class.
/*!
Base engine class to which every engine will inherit from.
Created by Daniel Thompson, P15230940.
*/

#pragma once

#include <string>

#include <glm\glm.hpp>

class Game;
class CameraComponent;
class PhysicsComponent;
class Model;

class EngineCore
{
public:
	static int i_Width;
	static int i_Height;

	virtual ~EngineCore() {};

	virtual bool InitWindow(int IWidth, int IHeight, std::string IWindowName) = 0;
	virtual bool RunEngine(Game& IGame) = 0;
	virtual void SetCamera(const CameraComponent* c_ICamera) = 0;

	virtual void RenderColouredBackground(float f_IRed, float f_IGreen, float f_IBlue) = 0;
	virtual void RenderText(std::string text, float x, float y, float scale, glm::vec3 colour) = 0;

	virtual void DrawCube(const glm::mat4& m4_IModelMatrix) = 0;
	virtual void DrawDebug(PhysicsComponent* c_PhysicsComponent, const glm::mat4& m4_IModelMatrix) = 0;
	virtual void DrawModel(Model* model, glm::mat4& modelMatrix) = 0;
};