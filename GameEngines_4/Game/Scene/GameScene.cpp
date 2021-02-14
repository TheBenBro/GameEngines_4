#include "GameScene.h"

GameScene::GameScene()
{
	shape = nullptr;
	shape2 = nullptr;
}

GameScene::~GameScene()
{
	delete shape;
	shape = nullptr;

	delete shape2;
	shape2 = nullptr;
}

bool GameScene::OnCreate()
{
	std::cout << "Game scene" << std::endl;
	Vertex v;
	std::vector<Vertex> vertexList;
	vertexList.reserve(3);
	v.position = glm::vec3(-0.5f, 0.5f, 0.0f);
	vertexList.push_back(v);
	v.position = glm::vec3(-0.5f, -0.5f, 0.0f);
	vertexList.push_back(v);
	v.position = glm::vec3(0.5f, -0.5f, 0.0f);
	vertexList.push_back(v);

	Vertex v2;
	std::vector<Vertex> vertexList2;
	vertexList2.reserve(3);
	v2.position = glm::vec3(-0.5f, 0.5f, 0.0f);
	vertexList2.push_back(v2);
	v2.position = glm::vec3(0.5f, 0.5f, 0.0f);
	vertexList2.push_back(v2);
	v2.position = glm::vec3(0.5f, -0.5f, 0.0f);
	vertexList2.push_back(v2);

	Model* model = new Model();
	Model* model2 = new Model();

	model->AddMesh(new Mesh(vertexList));
	model2->AddMesh(new Mesh(vertexList2));

	shape = new GameObject(model);
	shape2 = new GameObject(model2);
	return true;
}

void GameScene::Update(const float deltaTime_)
{
	//std::cout << deltaTime_ << std::endl;
}

void GameScene::Render()
{
	shape->Render();
	shape2->Render();
}
