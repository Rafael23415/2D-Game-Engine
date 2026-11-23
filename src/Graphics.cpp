#include "Graphics.h"

#include <SDL3/SDL.h>
#include <glad/glad.h>

#include <iostream>
#include <stdexcept>
#include <string>


namespace Engineering2D
{
	struct WindowImpl
	{
		std::unique_ptr<SDL_Window> m_window;

		WindowImpl(const char* name, const Vector2DInt windowSize)
		{
			SDL_CreateWindow(name, windowSize.x, windowSize.y, SDL_WINDOW_OPENGL);
		};

		~WindowImpl()
		{
			SDL_DestroyWindow(m_window.get());
		};

		void SwapWindow()
		{
			SDL_GL_SwapWindow(m_window.get());
		};
	};

	struct ContextImpl
	{
		std::unique_ptr<SDL_GLContext> m_context;


		ContextImpl(SDL_Window* window)
		{
			SDL_GL_CreateContext(window);
		};

		~ContextImpl() {
			SDL_GL_DestroyContext(*m_context.get());
		};
	};

	Graphics::Graphics(const char* name, const Vector2DInt windowSize)
	{
		if (!SDL_Init(SDL_INIT_VIDEO)) {
			throw std::runtime_error(std::string("SDL_Init failed: ") + SDL_GetError());
		}

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

		m_window = std::make_unique<WindowImpl>(name, windowSize.x, windowSize.y);
		if (!m_window) {
			throw std::runtime_error(std::string("Failed to create SDL Window: ") + SDL_GetError());
			SDL_Quit();
		}


		m_context = std::make_unique<ContextImpl>(m_window);
		if (!m_context) {
			throw std::runtime_error(std::string("Failed to create OpenGL context: ") + SDL_GetError());
			m_window.reset();
			SDL_Quit();
		}

		if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
			throw std::runtime_error(std::string("Failed to initialize GLAD"));
			m_context.reset();
			m_window.reset();
			SDL_Quit();
		}
	}
	
	Graphics::~Graphics()
	{
		if (m_context)
		{
			m_context.reset();
		}
		
		if (m_window)
		{
			m_window.reset();
		}
		
		SDL_Quit();
	}

	void Graphics::ClearRenderer()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Graphics::SwapWindow()
	{
		SDL_GL_SwapWindow(m_window.get()->SwapWindow());
	}
}
