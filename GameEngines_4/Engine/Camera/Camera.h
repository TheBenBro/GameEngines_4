#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../FX/LightSource.h"
#include <vector>
#include "../Math/Plane.h"

class Planes {
public:
	glm::vec3 position;
	glm::vec3 topLeft;
	glm::vec3 topRight;
	glm::vec3 bottomLeft;
	glm::vec3 bottomRight;
	static float GetFrontNormal(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2);
	static float GetRightNormal(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2);
	//Planes(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, float d);
};

class Camera
{
public:
	Camera();
	~Camera();

	void SetPosition(glm::vec3 position_);
	void SetRotation(float yaw_, float pitch_);
	void CreatePlanes();
	glm::mat4 GetView() const;
	glm::mat4 GetPerspective() const;
	glm::mat4 GetOrthographic() const;
	float GetNearPlane() const;
	float GetFarPlane() const;
	glm::vec3 GetPosition() const;

	void AddLightSource(LightSource* lightSource_);
	std::vector<LightSource*> getLights();
	glm::vec3 GetPlanesNormal(int plane_)const;
	bool IsPastPlane(enum PlaneType plane_);
	void ProcessMouseMovement(glm::vec2 offset_);
	void ProcessMouseZoom(int y_);
private:
	enum planeType {TOP,BOTTOM,FRONT,BACK,LEFT,RIGHT};

	void UpdateCameraVectors();
	glm::vec3 position;
	glm::mat4 perspective, orthographic, view;
	float fieldOfView;
	float yaw, pitch;
	float nearPlane, farPlane;
	glm::vec3 forward, up, right, worldUp;
	Plane planes[6];
	std::vector<LightSource*> lights;
	Planes far;
	Planes near;
};

#endif // !CAMERA_H