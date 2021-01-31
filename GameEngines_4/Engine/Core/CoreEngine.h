#ifndef COREENGINE_H
#define COREENGINE_H
#include "WIndow.h"

#include <memory>
class CoreEngine
{
public:
	//Disables the creation of copy and move contructors
	CoreEngine(const CoreEngine&) = delete;
	CoreEngine(CoreEngine&&) = delete;
	CoreEngine& operator=(const CoreEngine&) = delete;
	CoreEngine& operator=(CoreEngine&&) = delete;


	//returns a reference this Object
	static CoreEngine* GetInstance();

	bool OnCreate(std::string name_, int width_, int height_);
	void Run();
	bool GetIsRunning();
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
	//Keeps track of wether
	bool isRunning;
};
#endif // !COREENGINE_H
