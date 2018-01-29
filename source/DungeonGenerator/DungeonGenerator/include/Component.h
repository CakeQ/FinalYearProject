#pragma once

#include <string>

class Component
{
public:
	virtual void Update() = 0;
	virtual void Message(const std::string s_IMessage) = 0;
};