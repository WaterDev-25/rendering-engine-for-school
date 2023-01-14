#ifndef CWINDOWOPENGL46_HPP
#define CWINDOWOPENGL46_HPP

#include <string>
#include <memory>
#include <stdexcept>

#include <GL/glew.h>
#include <SDL2/SDL.h>
//#include <SDL2/SDL_opengl.h>

#include "iwindow.hpp"

class CWindowOpenGL46 : public IWindow
{
public:
	CWindowOpenGL46(unsigned int width, unsigned int height, std::string title);
	~CWindowOpenGL46() override;

	void Init() final;

	SDL_Window* GetHandle();

private:
	std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> mp_Window;

	SDL_GLContext m_Context;

	unsigned int m_Width;
	unsigned int m_Height;

	std::string m_Title;
};

#endif // CWINDOWOPENGL46_HPP
