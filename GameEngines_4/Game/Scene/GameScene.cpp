#include "GameScene.h"

GameScene::GameScene()
{
	shape = nullptr;
	light = nullptr;
}

GameScene::~GameScene()
{
	delete shape;
	shape = nullptr;

	model = nullptr;

	delete light;
	light = nullptr;
}

bool GameScene::OnCreate()
{
	std::cout << "Game scene" << std::endl;

	CoreEngine::GetInstance()->SetCamera(new Camera());
	CoreEngine::GetInstance()->GetCamera()->SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));
	CoreEngine::GetInstance()->GetCamera()->AddLightSource(new LightSource(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.1f, 0.5f, 0.5f));
	TextureHandle::GetInstance()->CreateTexture("CheckerboardTexture", "./Resources/Textures/CheckerboardTexture.png");



	model = new Model("Resources/Models/Dice.obj ", "Resources/Materials/Dice.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	
	shape = new GameObject(model);
	return true;
}

void GameScene::Update(const float deltaTime_)
{
	shape->Update(deltaTime_);
}

void GameScene::Render()
{
	shape->Render(CoreEngine::GetInstance()->GetCamera());
}
