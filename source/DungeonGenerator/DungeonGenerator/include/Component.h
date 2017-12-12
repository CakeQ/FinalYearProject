#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/mat4x4.hpp>

#include <map>
#include <vector>

class Component
{
private:
	glm::vec3 v3_WorldPos;

public:
	Component() {};
	virtual ~Component() {};

	void Transform(glm::vec3 v3_ITransform) { v3_WorldPos += v3_ITransform; };
	void SetWorldPos(glm::vec3 v3_IWorldPos) { v3_WorldPos = v3_IWorldPos; };
	void SetWorldPos(float f_IX, float f_IY, float f_IZ)
	{
		v3_WorldPos.x = f_IX;
		v3_WorldPos.y = f_IY;
		v3_WorldPos.z = f_IZ;
	};
	
	glm::vec3 GetWorldPos() { return v3_WorldPos; };

	virtual void Update() = 0;
	virtual void HandleInput(const std::vector<bool>& vt_IKeyBuffer, const glm::vec2 v2_IMousebuffer) = 0;
};