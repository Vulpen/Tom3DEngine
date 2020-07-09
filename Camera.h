#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


class Camera
{
public:
	glm::mat4 getViewMatrix() const;
	virtual void rotate(float yaw, float pitch) {}
	virtual void setPosition(const glm::vec3& position) {}
	virtual void move(const glm::vec3& offset) {}

	const glm::vec3& getLook() const;
	const glm::vec3& getRight() const;
	const glm::vec3& getUp() const;
	const glm::vec3& getPosition() const;
	const float getYaw() const;
	const float getPitch() const;

	float getFOV() { return mFOV; }
	float setFOV(float in) { mFOV = in; }
protected:
	Camera();

	float mFOV;
	float mYaw; // In Radians
	float mPitch;
	glm::vec3 mPosition;
	glm::vec3 mTargetPos;
	glm::vec3 mUp;
	glm::vec3 mLook;
	glm::vec3 mRight;
	const glm::vec3 WORLD_UP;
};

class FPSCamera : public Camera
{
public:
	FPSCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), float yaw = glm::pi<float>(), float pitch = 0.0f);

	virtual void setPosition(const glm::vec3& position);
	virtual void rotate(float yaw, float pitch);
	virtual void move(const glm::vec3& offset);

private:
	void updateCameraVectors();
};

class OrbitCamera : public Camera {
public:
	OrbitCamera();

	virtual void rotate(float yaw, float pitch); // In Degrees

	void setLookAt(const glm::vec3& target);
	void setRadius(float radius);

private:
	void updateCameraVectors();
	float mRadius;

};


