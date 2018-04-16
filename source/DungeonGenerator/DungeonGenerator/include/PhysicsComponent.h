#pragma once

#include <Box2D\Box2D.h>

#include "Component.h"

class PhysicsComponent : public Component
{
public:
	b2BodyDef b2_BodyDef;
	b2Body* b2_Body;
	b2PolygonShape b2_Shape;
	b2FixtureDef b2_FixtureDef;
	
	void Update(float f_IDeltaTime) override
	{

	}

	void Message(const std::string s_IMessage) override 
	{
		
	}
};