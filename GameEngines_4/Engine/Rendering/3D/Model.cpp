#include "Model.h"



Model::Model(GLuint shaderProgram_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_)
	: meshes(std::vector<Mesh*>()), shaderProgram(0), position(glm::vec3()),
	angle(0.0f), rotation(glm::vec3(0.0f, 1.0f, 0.0f)), scale(glm::vec3(1.0f))
{
	shaderProgram = shaderProgram_;
	position = position_;
	angle = angle_;
	rotation = rotation_;
	scale = scale_;
}

Model::~Model()
{
	if (meshes.size() > 0) {
		//for each m in meshes, delete them
		for (auto m : meshes) {
			delete m;
			m = nullptr;
		}
		meshes.clear();
	}
}

void Model::Render(Camera* camera_)
{
	glUseProgram(shaderProgram);
	//Call render for each mesh
	for (auto m : meshes) {
		m->Render(camera_,GetTransform());
	}
}

void Model::AddMesh(Mesh* mesh_)
{
	//adds mesh to the back of the list
	meshes.push_back(mesh_);
}

glm::vec3 Model::GetPosition() const
{
	return position;
}

float Model::GetAngle() const
{
	return angle;
}

glm::vec3 Model::GetRotation() const
{
	return rotation;
}

glm::vec3 Model::GetScale() const
{
	return scale;
}

void Model::SetPosition(glm::vec3 position_)
{
	position = position_;
}

void Model::SetAngle(float angle_)
{
	angle = angle_;
}

void Model::SetRotation(glm::vec3 rotation_)
{
	rotation = rotation_;
}

void Model::SetScale(glm::vec3 scale_)
{
	scale = scale_;
}

glm::mat4 Model::GetTransform() const
{
	glm::mat4 model;
	model = glm::translate(model, position);
	model = glm::rotate(model, angle, rotation);
	model = glm::scale(model, scale);
	return model;
}
