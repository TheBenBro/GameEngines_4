#include "Mesh.h"

Mesh::Mesh(SubMesh& subMesh_, GLuint shaderProgram_)
{
	{
		VAO = 0;
		VBO = 0;
		shaderProgram = 0;
		textureID = 0;
		modelLoc = 0;
		viewLoc = 0;
		projectionLoc = 0;
		viewPos = 0;
		lightPos = 0;
		ambient = 0;
		diffuse = 0;
		specular = 0;
		colour = 0;
		shininessPos = 0;
		transparencyPos = 0;
		diffuseMapPos = 0;
		ambientPos = 0;
		diffusePos = 0;
		specularPos = 0;
	}
	subMesh = subMesh_;
	shaderProgram = shaderProgram_;
	
	GenerateBuffers();
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	if (subMesh.vertexList.size() > 0) {
		subMesh.vertexList.clear();
	}
	if (subMesh.meshIndices.size() > 0) {
		subMesh.meshIndices.clear();
	}

}

void Mesh::Render(Camera* camera_, std::vector<glm::mat4>& instances_)
{
	glUniform1i(diffuseMapPos, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, subMesh.material.diffuseMap);
	{
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));

		glUniform3fv(viewPos, 1, glm::value_ptr(camera_->GetPosition()));
		glUniform3fv(lightPos, 1, glm::value_ptr(camera_->getLights()[0]->getPosition()));
		glUniform3fv(colour, 1, glm::value_ptr(camera_->getLights()[0]->getLightColour()));

		glUniform1f(ambient, camera_->getLights()[0]->getAmbientValue());
		glUniform1f(diffuse, camera_->getLights()[0]->getDiffuseValue());
		glUniform1f(specular, camera_->getLights()[0]->getSpecularValue());

		glUniform1f(shininessPos, subMesh.material.shininess);
		glUniform1f(transparencyPos, subMesh.material.transparancy);

		glUniform3f(ambientPos, subMesh.material.ambient.x, subMesh.material.ambient.y, subMesh.material.ambient.z);
		glUniform3f(diffusePos, subMesh.material.diffuse.x, subMesh.material.diffuse.y, subMesh.material.diffuse.z);
		glUniform3f(specularPos, subMesh.material.specular.x, subMesh.material.specular.y, subMesh.material.specular.z);
	}
	
	glBindVertexArray(VAO);

	glEnable(GL_DEPTH_TEST);

	for (int i = 0; i < instances_.size(); i++) {
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(instances_[i]));
		if (instances_[i][3].z < camera_->GetPlanesNormal(0).z) {
			std::cout << "NOT RENDERED" << std::endl;
			
		}
		glDrawArrays(GL_TRIANGLES, 0, subMesh.vertexList.size());
		//
	}
	
	

	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::GenerateBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, subMesh.vertexList.size() * sizeof(Vertex),
		&subMesh.vertexList[0], GL_STATIC_DRAW);
	//position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	//normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	//Texture Coordinates
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, textureCoordinates));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	modelLoc = glGetUniformLocation(shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projectionLoc = glGetUniformLocation(shaderProgram, "projection");

	viewPos = glGetUniformLocation(shaderProgram, "cameraPosition");
	lightPos = glGetUniformLocation(shaderProgram, "lights.lightPos");
	colour = glGetUniformLocation(shaderProgram, "lights.lightColour");

	ambient = glGetUniformLocation(shaderProgram, "lights.ambient");
	diffuse = glGetUniformLocation(shaderProgram, "lights.diffuse");
	specular = glGetUniformLocation(shaderProgram, "lights.specular");

	shininessPos = glGetUniformLocation(shaderProgram, "material.shininess");
	transparencyPos = glGetUniformLocation(shaderProgram, "material.transparancy");
	diffuseMapPos = glGetUniformLocation(shaderProgram, "material.diffuseMap");
	ambientPos = glGetUniformLocation(shaderProgram, "material.ambient");
	diffusePos = glGetUniformLocation(shaderProgram, "material.diffuse");
	specularPos = glGetUniformLocation(shaderProgram, "material.specular");
}
