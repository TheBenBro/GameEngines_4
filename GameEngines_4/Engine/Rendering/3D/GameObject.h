#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Model.h"
class GameObject
{
public:

	GameObject(Model* model_, glm::vec3 position_ = glm::vec3());

	~GameObject();

	void Update(const float deltaTime_);
	void Render(Camera* camera_);

	glm::vec3 GetPosition() const;
	float getAngle() const;
	glm::vec3 GetRotation() const;
	glm::vec3 GetScale() const;
	std::string GetTag() const;
	BoundingBox GetBoundingBox() const;
	bool GetHit() const;

	void SetPosition(glm::vec3 position_);
	void SetAngle(float angle_);
	void SetRotation(glm::vec3 rotation_);
	void SetScale(glm::vec3 scale_);
	void SetTag(std::string tag_);
	void SetHit(bool hit_, int buttonType);
private:
	Model* model;
	unsigned int modelInstance;
	glm::vec3 position;
	float angle;
	glm::vec3 rotation;
	glm::vec3 scale;
	std::string tag;

	BoundingBox boundingBox;

	bool hit;
};

#endif