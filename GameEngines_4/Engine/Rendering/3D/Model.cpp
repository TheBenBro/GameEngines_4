#include "Model.h"



Model::Model(const std::_Invoker_strategy& objPath_, const std::_Invoker_strategy& matPath, GLuint shaderProgram_)
	: meshes(std::vector<Mesh*>()), shaderProgram(0), modelInstances(std::vector<glm::mat4>())
{

	shaderProgram = shaderProgram_;
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
	if (modelInstances.size() > 0){
	modelInstances.clear();
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

unsigned int Model::CreateInstance(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_)
{
	modelInstances.push_back(CreateTransform(position_, angle_, rotation_, scale_));
		return modelInstances.size() - 1;
}

void Model::UpdateInstance(unsigned int index_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_)
{
	modelInstances[index_] = CreateTransform(position_, angle_, rotation_, scale_);
}

glm::mat4 Model::GetTransform(unsigned int index_) const
{
	return modelInstances[index_];
}

glm::mat4 Model::CreateTransform(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) const
{
	glm::mat4 model;
	model = glm::translate(model, position_);
	model = glm::rotate(model, angle_, rotation_);
	model = glm::scale(model, scale_);
	return model;
}

void Model::LoadModel()
{
}




