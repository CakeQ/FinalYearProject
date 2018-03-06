#pragma once

#include <imgui\imgui.h>
#include <imgui\imgui_impl_glfw_gl3.h>
#include <imgui\imgui_internal.h>

#include "EngineCoreBase.h"
#include "Scene.h"

class GUI
{
private:
	EngineCore* e_GameEngine;

public:
	GUI(EngineCore* e_IEngine)
	{

		ImGui::CreateContext();

	};


};
