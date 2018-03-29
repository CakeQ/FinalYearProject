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

	void Draw(Shader* s_IShader, glm::mat4 m4_IModelMatrix)
	{
		std::cout << "drawing debug" << std::endl;
		//set up vertex array
		GLfloat glverts[16]; //allow for polygons up to 8 vertices
		glVertexPointer(2, GL_FLOAT, 0, glverts); //tell OpenGL where to find vertices
		glEnableClientState(GL_VERTEX_ARRAY); //use vertices in subsequent calls to glDrawArrays

											  //fill in vertex positions as directed by Box2D
		for (int i = 0; i < vertexCount; i++) {
			glverts[i * 2] = vertices[i].x;
			glverts[i * 2 + 1] = vertices[i].y;
		}

		glUniformMatrix4fv(glGetUniformLocation(s_IShader->ui_ShaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(m4_IModelMatrix));

		//draw solid area
		glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
		glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);

		//draw lines
		glLineWidth(3); //fat lines
		glColor4f(1, 0, 1, 1); //purple
		glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
		};


		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		
		glVertexPointer(3, GL_FLOAT, 0, f_Vertices);
		glDrawArrays(GL_QUADS, 0, 32);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
};