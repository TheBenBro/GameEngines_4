#include "Camera.h"

#include "../Core/CoreEngine.h"

Camera::Camera() : fieldOfView(0.0f), forward(glm::vec3()),up(glm::vec3()),
	right(glm::vec3()),worldUp(glm::vec3()), nearPlane(0.0f), farPlane(0.0f),
	yaw(0.0f), pitch(0.0f), perspective(glm::mat4()), orthographic(glm::mat4()), view(glm::mat4()), lights(std::vector<LightSource*>())
{
	fieldOfView = 45.0f;
	forward = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	worldUp = up;
	nearPlane = 2.0f;
	farPlane = 50.0f;
	yaw = -90.0f;
	pitch = 0.0f;

	perspective = glm::perspective(fieldOfView,
		CoreEngine::GetInstance()->GetScreenWidth() /
		CoreEngine::GetInstance()->GetScreenHeight(),
		nearPlane, farPlane);

	orthographic = glm::ortho(0.0f, CoreEngine::GetInstance()->GetScreenWidth(),
		0.0f, CoreEngine::GetInstance()->GetScreenHeight(),
		-1.0f, 1.0f);

	UpdateCameraVectors();
}

Camera::~Camera()
{
	for (auto l : lights) {
		delete l;
		l = nullptr;
	}
	lights.clear();
}

void Camera::SetPosition(glm::vec3 position_)
{
	position = position_;
	UpdateCameraVectors();
}

void Camera::SetRotation(float yaw_, float pitch_)
{
	yaw = yaw_;
	pitch = pitch_;
	UpdateCameraVectors();
}

glm::mat4 Camera::GetView() const
{
	return view;
}

glm::mat4 Camera::GetPerspective() const
{
	return perspective;
}

glm::mat4 Camera::GetOrthographic() const
{
	return orthographic;
}

glm::vec3 Camera::GetPosition() const
{
	return position;
}

void Camera::AddLightSource(LightSource* lightSource_)
{
	lights.push_back(lightSource_);
}

std::vector<LightSource*> Camera::getLights()
{
	return lights;
}










void Camera::UpdateCameraVectors()
{
	forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward.y = sin(glm::radians(pitch));
	forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	forward = glm::normalize(forward);

	right = glm::normalize(glm::cross(forward, worldUp));

	up = glm::normalize(glm::cross(right, forward));

	view = glm::lookAt(position, position + forward, up);
}
