#include "Camera.h"

Camera::Camera()
	:mPosition(glm::vec3(0.0f, 0.0f, 0.0f)), mFOV(45.0f),
	mTargetPos(glm::vec3(0.0f, 0.0f, 0.0f)),
	mUp(glm::vec3(0.0f, 1.0f, 0.0f)),
	mRight(0.0f, 0.0f, 0.0f),
	WORLD_UP(0.0f, 1.0f, 0.0f),
	mYaw(0.0f),
	mPitch(0.0f),
	mLook(0.0f,0.0f,-1.0f),
	CameraTransform()
{

}

glm::mat4 Camera::getViewMatrix(){
	//return glm::lookAt(mPosition, mTargetPos, mUp); //Note: this creates a view matrix; inverse of the actual camera matrix
	return glm::lookAt(CameraTransform.GetPosition(), CameraTransform.GetLookTarget(), CameraTransform.GetUp());
}

float Camera::getYaw(){
	return mYaw;
}

float Camera::getPitch(){
	return mPitch;
}

glm::vec3 Camera::getLook()
{
	//return mLook;
	return CameraTransform.GetForward();
}
glm::vec3 Camera::getRight()
{
	//return mRight;
	return CameraTransform.GetRight();
}
glm::vec3 Camera::getUp()
{
	//return mUp;
	return CameraTransform.GetUp();
}
glm::vec3 Camera::getPosition()
{
	//return mPosition;
	return CameraTransform.GetPosition();
}

//----------
//FPS Camera
//----------
FPSCamera::FPSCamera(glm::vec3 position, float yaw, float pitch) {
	mPosition = position;
	mYaw = yaw;
	mPitch = pitch;
	updateCameraVectors();
}

void FPSCamera::setPosition(const glm::vec3& position)
{
	mPosition = position;
	CameraTransform.Position = position;
}
void FPSCamera::rotate(float yaw, float pitch)
{
	mYaw += glm::radians(yaw);
	mPitch += glm::radians(pitch);

	mPitch = glm::clamp(mPitch, -glm::pi<float>() / 2.0f + 0.1f, glm::pi<float>() / 2.0f - 0.1f);
	/*if (mYaw > glm::pi<float>()) mYaw -= glm::pi<float>();
	if (mYaw < -glm::pi<float>()) mYaw += glm::pi<float>();*/
	//updateCameraVectors();
	CameraTransform.ApplyYawPitchR(mYaw, mPitch);
}
void FPSCamera::move(const glm::vec3& offset)
{
	mPosition = mPosition + offset;
	updateCameraVectors();
	CameraTransform.Move(offset);
}

void FPSCamera::updateCameraVectors()
{
	glm::vec3 look;
	look.x = cosf(mPitch) * sinf(mYaw);
	look.y = sinf(mPitch);
	look.z = cosf(mPitch) * cosf(mYaw);

	mLook = glm::normalize(look);

	mRight = glm::normalize(glm::cross(mLook, WORLD_UP));
	mUp = glm::normalize(glm::cross(mRight, mLook));

	mTargetPos = mPosition + mLook;
	mTargetPos = CameraTransform.GetLookTarget();
}

//------------
//Orbit Camera
//------------
OrbitCamera::OrbitCamera()
	:mRadius(10.0f)
{

}

void OrbitCamera::setLookAt(const glm::vec3& target) {
	mTargetPos = target;
}

void OrbitCamera::setRadius(float radius) {
	mRadius = glm::clamp(radius, 2.0f, 80.0f);
}

void OrbitCamera::rotate(float yaw, float pitch) {
	mYaw = glm::radians(yaw);
	mPitch = glm::radians(pitch);

	mPitch = glm::clamp(mPitch, -glm::pi<float>() / 2.0f + 0.1f, glm::pi<float>() / 2.0f - 0.1f);

	updateCameraVectors();
}

void OrbitCamera::updateCameraVectors() {
	//Spherical to Cartesian Coordinates
	mPosition.x = mTargetPos.x + mRadius * cosf(mPitch) * sinf(mYaw);
	mPosition.y = mTargetPos.y + mRadius * sinf(mPitch);
	mPosition.z = mTargetPos.z + mRadius * cosf(mPitch) * cosf(mYaw);
}