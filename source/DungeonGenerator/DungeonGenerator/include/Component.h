#pragma once

#include <string>

class Component
{
public:
	virtual void Update(float f_IDeltaTime) = 0;
	virtual void Message(const std::string s_IMessage) = 0;
};