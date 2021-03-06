#ifndef COREENGINE_H
#define COREENGINE_H

#include <memory>
#include "Window.h"
#include "Timer.h"
#include "Debug.h"
#include "GameInterface.h"
#include "Scene.h"

#include "../Rendering/3D/GameObject.h"
#include "../Graphics/ShaderHandler.h"

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

	void SetGameInterface(GameInterface* gameInterface_);
	void SetCurrentScene(int sceneNum);
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

	int currentSceneNum;
};
#endif // !COREENGINE_H
