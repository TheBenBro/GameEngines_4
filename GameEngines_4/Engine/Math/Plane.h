#ifndef PLANE_H
#define PLANE_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
struct Plane
{
	float x, y, z, d ;
	inline Plane():x(0),y(0),z(0),d(0)
	{ }
	inline Plane(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2) {
		glm::vec3 v = v1 - v0;
		glm::vec3 u = v2 - v0;
		glm::vec3 n = glm::normalize(glm::cross(v, u));
		set(n.x, n.y, n.z, glm::dot(n, v0));
	}
	inline void set(float x_, float y_, float z_,float d_) {
		x = x_;
		y = y_;
		z = z_;
		d = d_;
	}
	inline glm::vec3 GetNormal(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2)const
	{
		glm::vec3 v = v1 - v0;
		glm::vec3 u = v2 - v0;
		glm::vec3 n = glm::normalize(glm::cross(v, u));
		return n;
	}
};
#endif