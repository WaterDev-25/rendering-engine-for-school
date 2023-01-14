#include "cwindowopengl46.hpp"

CWindowOpenGL46::CWindowOpenGL46(unsigned int width, unsigned int height, std::string title)
	: mp_Window(nullptr, SDL_DestroyWindow), m_Width(width), m_Height(height), m_Title(title)
{
	this->Init();
}

CWindowOpenGL46::~CWindowOpenGL46()
{
	SDL_GL_DeleteContext(this->m_Context);

	this->mp_Window.release();

	SDL_Quit();
}

// Initialize OpenGL 4.6 window
void CWindowOpenGL46::Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		throw std::runtime_error("SDL2 initialization failed");

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

	this->mp_Window.reset(SDL_CreateWindow(this->m_Title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->m_Width, this->m_Height, SDL_WINDOW_OPENGL));

	if (!this->mp_Window) // nullptr?
		throw std::runtime_error("SDL2 window initialization failed");

	this->m_Context = SDL_GL_CreateContext(this->mp_Window.get());

	if (!this->m_Context)
		throw std::runtime_error("OpenGL context initialization failed");

	glewExperimental = true;

	if (glewInit() != GLEW_OK)
		throw std::runtime_error("GLEW initialization failed");
}

SDL_Window* CWindowOpenGL46::GetHandle()
{
	return this->mp_Window.get();
}
