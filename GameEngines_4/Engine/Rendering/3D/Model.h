#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"
#include <glm/gtc/matrix_transform.hpp> 
#include <string>
class Model
{
public:
	Model(const std::_Invoker_strategy& objPath_, const std::_Invoker_strategy& matPath,  GLuint shaderProgram_);
	~Model();

	void Render(Camera* camera_);
	void AddMesh(Mesh* mesh_);
	unsigned int CreateInstance(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_);
	void UpdateInstance(unsigned int index_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_);
	glm::mat4 GetTransform(unsigned int index_) const;


private:
	glm::mat4 CreateTransform(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_)const;
	void LoadModel();
	std::vector<Mesh*> meshes;
	GLuint shaderProgram;
	std::vector<glm::mat4> modelInstances;


};

#endif // !MODEL_H