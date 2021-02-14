#include "StartScene.h"

StartScene::StartScene()
{

}

StartScene::~StartScene()
{
}

bool StartScene::OnCreate()
{
	std::cout << "start scene" << std::endl;
	if (CoreEngine::GetInstance()->GetCurrentScene() == 0) {
		CoreEngine::GetInstance()->SetCurrentScene(1);
	}
	return true;
}

void StartScene::Update(const float deltaTime_)
{
}

void StartScene::Render()
{
}
