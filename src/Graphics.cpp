#include "Graphics.h"

#include <SDL3/SDL.h>
#include <glad/glad.h>

#include <iostream>
#include <stdexcept>
#include <string>


namespace Engineering2D
{
	// ---------------------------------------------------------
	// Window implementation
	// ---------------------------------------------------------

	struct Graphics::WindowImpl
	{
		std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_windowPtr;

		WindowImpl(const char* name, const Vector2DInt windowSize) : m_windowPtr(SDL_CreateWindow(name, windowSize.x, windowSize.y, SDL_WINDOW_OPENGL), SDL_DestroyWindow)
		{
			if (!m_windowPtr)
			{
				throw std::runtime_error(std::string("Failed to create SDL Window: ") + SDL_GetError());
			}
		};

		void SwapWindow()
		{
			SDL_GL_SwapWindow(m_windowPtr.get());
		};
	};

	// ---------------------------------------------------------
	// OpenGL context implementation
	// ---------------------------------------------------------

	struct Graphics::ContextImpl
	{
		SDL_GLContext m_contextPtr = nullptr;

		ContextImpl(WindowImpl& window)
		{
			m_contextPtr = SDL_GL_CreateContext(window.m_windowPtr.get());

			if (!m_contextPtr)
			{
				throw std::runtime_error(std::string("Failed to create OpenGL context: ") + SDL_GetError());
			}
		};
	};

	// ---------------------------------------------------------
	// Graphics
	// ---------------------------------------------------------

	Graphics::Graphics(const char* name, const Vector2DInt windowSize)
	{
		if (!SDL_Init(SDL_INIT_VIDEO)) {
			throw std::runtime_error(std::string("SDL_Init failed: ") + SDL_GetError());
		}

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

		try {
			m_window = std::make_unique<WindowImpl>(name, windowSize);
			if (!m_window) {
				throw std::runtime_error(std::string("Failed to create SDL Window: ") + SDL_GetError());
				SDL_Quit();
			}


			m_context = std::make_unique<ContextImpl>(*m_window);
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
		catch (const std::exception& e)
		{
			m_context.reset();
			m_window.reset();

			std::cout << e.what() << std::endl;
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

	void Graphics::ClearContext()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Graphics::SwapWindow()
	{
		if(m_window)
		{
			m_window.get()->SwapWindow();
		}
	}
}
