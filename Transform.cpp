#include "Transform.h"

using namespace glm;

Transform::Transform()
	:Position(vec3(0.0f,0.0f,0.0f)),
	RotationQuaternion(quat(vec3(0,0,0)))
{}

glm::vec3 Transform::GetForward() {
	return normalize(rotate(RotationQuaternion, vec3(0.0f, 0.0f, -1.0f)));
}

glm::vec3 Transform::GetRight() {
	return normalize(rotate(RotationQuaternion, vec3(1.0f, 0.0f, 0.0f)));
}

glm::vec3 Transform::GetUp() {
	return normalize(rotate(RotationQuaternion, vec3(0.0f, 1.0f, 0.0f)));
}

glm::vec3 Transform::GetPosition() {
	return Position;
}

glm::vec3 Transform::GetLookTarget() {
	return GetPosition() + GetForward();
}

void Transform::ApplyYawPitch(float yaw, float pitch)
{
	quat newRot = quat(vec3(radians(pitch), radians(yaw), 0.0f));
	RotationQuaternion = RotationQuaternion * newRot;
}