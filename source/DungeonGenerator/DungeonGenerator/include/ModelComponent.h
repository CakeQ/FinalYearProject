#pragma once

#include <vector>

#include "Component.h"
#include "Mesh.h"
#include "Model.h"
#include "Shader.h"

class ModelComponent : public Component
{
private:
	GLuint ui_ShaderProgram;

public:
	Model* m_Model;
	bool b_Hidden = false;

	void SetHidden(bool b_IState)
	{
		b_Hidden = b_IState;
	};

	void Update() override {};
	void Message(const std::string s_IMessage) override {};
};
