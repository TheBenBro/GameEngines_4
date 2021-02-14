#include "Model.h"

Model::Model() :meshes(std::vector<Mesh*>())
{
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

void Model::Render()
{
	//Call render for each mesh
	for (auto m : meshes) {
		m->Render();
	}
}

void Model::AddMesh(Mesh* mesh_)
{
	//adds mesh to the back of the list
	meshes.push_back(mesh_);
}
