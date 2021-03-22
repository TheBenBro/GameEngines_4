#include "Window.h"

Window::Window()
{
	window = nullptr;
	context = nullptr;
}

Window::~Window()
{
	//called when a window object is destroyed
	OnDestroy();
}

bool Window::OnCreate(std::string name_, int width_, int height_)
{
	//If SDL Window does not initialize
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		Debug::FatalError("Failed to initialize SDL", "Window.cpp", __LINE__);
		return false;
	}
	//sets width and height
	this->width = width_;
	this->height = height_;

	SetPreAttributes();

	//Create window with OpenGL rendering
	window = SDL_CreateWindow(name_.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

	if (!window) {
		Debug::FatalError("Failed to create Window", "Window.cpp", __LINE__);
		return false;
	}
	context = SDL_GL_CreateContext(window);
	SetPostAttributes();


	//initializes GLEW
	GLenum err = glewInit();
	if (err != GLEW_OK) {

		Debug::FatalError("Failed to initialize GLEW", "Window.cpp", __LINE__);
		return false;
	}
	
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	glViewport(0, 0, width, height);
	return true;
}

void Window::OnDestroy()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	window = nullptr;
}

int Window::GetWidth() const
{
	return width;
}

int Window::GetHeight() const
{
	return height;
}

SDL_Window* Window::GetWindow() const
{
	return window;
}

void Window::SetPreAttributes()
{

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	//sets the OpenGL major and minor version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1);
	glewExperimental = GL_TRUE;

}

void Window::SetPostAttributes()
{
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
}
