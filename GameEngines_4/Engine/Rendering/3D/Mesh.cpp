#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex>& vertexList_, GLuint textureID_, GLuint shaderProgram_) : vertexList(std::vector < Vertex>())
{
	VAO = 0;
	VBO = 0;
	shaderProgram = 0;
	textureID = 0;
	textureLoc = 0;

	textureID = textureID_;
	vertexList = vertexList_;
	shaderProgram = shaderProgram_;
	GenerateBuffers();
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	vertexList.clear();
}

void Mesh::Render(Camera* camera_, glm::mat4 transform_)
{
	glUniform1i(textureLoc, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));

	glUniform1fv(viewPos, 1, glm::value_ptr(camera_->GetPosition()));
	glUniform1fv(lightPos, 1, glm::value_ptr(camera_->GetPosition()));
	glUniform1fv(colour, 1, glm::value_ptr(camera_->GetPosition()));

	glUniform1f(ambient, camera_->getLights());
	glUniform1f(diffuse, camera_->getLights());
	glUniform1f(specular, camera_->getLights());

	
	glBindVertexArray(VAO);

	glEnable(GL_DEPTH_TEST);

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform_));
	

	glDrawArrays(GL_TRIANGLES, 0, vertexList.size());
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glBindVertexArray(0);
}

void Mesh::GenerateBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexList.size() * sizeof(Vertex),
		&vertexList[0], GL_STATIC_DRAW);
	//position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	//normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	//Texture Coordinates
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, textureCoordinates));
	//colour
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, colour));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	modelLoc = glGetUniformLocation(shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projectionLoc = glGetUniformLocation(shaderProgram, "projection");
	textureLoc = glGetUniformLocation(shaderProgram, "inputTexture");

	viewPos = glGetUniformLocation(shaderProgram, "cameraPosition");
	lightPos = glGetUniformLocation(shaderProgram, "lights.lightPos");
	colour = glGetUniformLocation(shaderProgram, "lights.lightColour");

	ambient = glGetUniformLocation(shaderProgram, "lights.ambient");
	diffuse = glGetUniformLocation(shaderProgram, "lights.diffuse");
	specular = glGetUniformLocation(shaderProgram, "lights.specular");

}
