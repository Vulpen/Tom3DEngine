#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
class Transform
{
public:
	Transform();
	glm::vec3 GetPosition();
	glm::vec3 GetForward();
	glm::vec3 GetRight();
	glm::vec3 GetUp();
	glm::vec3 GetLookTarget();
	void ApplyYawPitch(float yaw, float pitch);


	glm::vec3 Position;
	glm::quat RotationQuaternion;
};

