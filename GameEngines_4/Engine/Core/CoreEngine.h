#ifndef COREENGINE_H
#define COREENGINE_H

#include <memory>
#include "Window.h"
#include "Timer.h"
#include "Debug.h"
#include "GameInterface.h"
#include "Scene.h"

#include "../Rendering/SceneGraph.h"
#include "../Rendering/3D/GameObject.h"

#include "../Graphics/ShaderHandler.h"
#include "../Graphics/MaterialHandler.h"
#include "../Rendering/Textures/TextureHandle.h"

#include "../Camera/Camera.h"

class CoreEngine
{
public:
	//Disables the creation of copy or move contructors
	CoreEngine(const CoreEngine&) = delete;
	CoreEngine(CoreEngine&&) = delete;
	CoreEngine& operator=(const CoreEngine&) = delete;
	CoreEngine& operator=(CoreEngine&&) = delete;


	//returns a reference this Object
	static CoreEngine* GetInstance();

	bool OnCreate(std::string name_, int width_, int height_);
	void Run();
	void Exit();

	bool GetIsRunning();
	int GetCurrentScene() const;
	float GetScreenWidth() const;
	float GetScreenHeight()const;
	Camera* GetCamera() const;

	void SetGameInterface(GameInterface* gameInterface_);
	void SetCurrentScene(int sceneNum);
	void SetCamera(Camera* camera_);
private:
	CoreEngine();
	~CoreEngine();
	void Update(const float deltaTime_);
	void Render();
	void OnDestroy();

	static std::unique_ptr<CoreEngine> engineInstance;
	friend std::default_delete<CoreEngine>;

	//Window class holds reference to sdl window
	Window* window;
	
	bool isRunning;

	Timer timer;
	unsigned int fps;

	GameInterface* gameInterface;
	Camera* camera;
	int currentSceneNum;
};
#endif // !COREENGINE_H
