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

void Camera::CreatePlanes()
{
	//Far Plane
	far.position = position + forward * farPlane;
	far.topLeft = far.position + (up * CoreEngine::GetInstance()->GetScreenHeight() / 2.0f) - (right * CoreEngine::GetInstance()->GetScreenWidth() / 2.0f);
	far.topRight = far.position + (up * CoreEngine::GetInstance()->GetScreenHeight() / 2.0f) + (right * CoreEngine::GetInstance()->GetScreenWidth() / 2.0f);
	far.bottomLeft = far.position - (up * CoreEngine::GetInstance()->GetScreenHeight() / 2.0f) - (right * CoreEngine::GetInstance()->GetScreenWidth() / 2.0f);
	far.bottomRight = far.position - (up * CoreEngine::GetInstance()->GetScreenHeight() / 2.0f) + (right * CoreEngine::GetInstance()->GetScreenWidth() / 2.0f);

	//near Plane
	near.position = position + forward * nearPlane;
	near.topLeft = near.position + (up * CoreEngine::GetInstance()->GetScreenHeight() / 2.0f) - (right * CoreEngine::GetInstance()->GetScreenWidth() / 2.0f);
	near.topRight = near.position + (up * CoreEngine::GetInstance()->GetScreenHeight() / 2.0f) + (right * CoreEngine::GetInstance()->GetScreenWidth() / 2.0f);
	near.bottomLeft = near.position - (up * CoreEngine::GetInstance()->GetScreenHeight() / 2.0f) - (right * CoreEngine::GetInstance()->GetScreenWidth() / 2.0f);
	near.bottomRight = near.position - (up * CoreEngine::GetInstance()->GetScreenHeight() / 2.0f) + (right * CoreEngine::GetInstance()->GetScreenWidth() / 2.0f);

	//right Plane

	planes[0] = Plane(far.topLeft, far.topRight, far.bottomLeft);
	planes[1] = Plane(near.topLeft, near.topRight, near.bottomLeft);
	//plane[2] = ;
}
float Planes::GetFrontNormal(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2)
{
	glm::vec3 v = v1 - v0;
	glm::vec3 u = v2 - v0;
	glm::vec3 n = glm::normalize(glm::cross(v, u));

	float d = glm::dot(n, v2);
	return d;
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

float Camera::GetNearPlane() const
{
	return nearPlane;
}

float Camera::GetFarPlane() const
{
	return farPlane;
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

glm::vec3 Camera::GetPlanesNormal(int plane_) const
{
	glm::vec3 tmp_Plane(0);
	int tmp = 0;
	switch (tmp)
	{
		case 0:
			tmp_Plane = far.position;
			break;
		default:
			break;
	}
	return tmp_Plane;
}

bool Camera::IsPastPlane(enum PlaneType plane_)
{
	switch (plane_)
	{
	case FRONT:
		//tmp_Plane = far.position;
		break;
	default:
		break;
	}
	return false;
}

void Camera::ProcessMouseMovement(glm::vec2 offset_)
{
	offset_ *= 0.05f;

	yaw += offset_.x;
	pitch -= offset_.y;

	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	if (pitch < -89.0f) {
		pitch = -89.0f;
	}
	if (yaw < 0.0f) {
		yaw += 360.0f;
	}
	if (yaw > 360.0f) {
		yaw -= 360.0f;
	}
	UpdateCameraVectors();
	CreatePlanes();
}

void Camera::ProcessMouseZoom(int y_)
{
	if (y_ < 0 || y_ > 0) {
		position += static_cast<float>(y_) * (forward * 2.0f);
	}
	UpdateCameraVectors();
	CreatePlanes();
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

