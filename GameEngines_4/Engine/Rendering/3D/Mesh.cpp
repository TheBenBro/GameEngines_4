#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex>& vertexList_) : vertexList(std::vector < Vertex>())
{
	VAO = 0;
	VBO = 0;
	vertexList = vertexList_;
	GenerateBuffers();
}

Mesh::~Mesh()
{
}

void Mesh::Render()
{
	glBindVertexArray(VAO);
	
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
}
