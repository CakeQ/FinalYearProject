#pragma once

#include "Component.h"

#define COLOUR_ADJUSTMENT_VALUE 0.001f

class ColourComponent : public Component
{
public:
	float f_ColourValue;

	ColourComponent() : f_ColourValue(0) {};

	void Update(float f_IDeltaTime) override
	{

	}

	void Message(const std::string s_IMessage) override
	{
		if (s_IMessage == "increase")
		{
			f_ColourValue += COLOUR_ADJUSTMENT_VALUE;
		}
		else if (s_IMessage == "decrease")
		{
			f_ColourValue -= COLOUR_ADJUSTMENT_VALUE;
		}
	}
};

class RedComponent : public ColourComponent {};
class GreenComponent : public ColourComponent {};
class BlueComponent : public ColourComponent {};