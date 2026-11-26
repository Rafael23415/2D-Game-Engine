#include "Graphics.h"

#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <stdexcept>
#include <string>

#include "Debug.h"


namespace Engineering2D
{
	using namespace Math;

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

			Debug::Log("Created window: ", name, " | ", windowSize);
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
				SDL_GL_DestroyContext(m_contextPtr);
			}

			Debug::Log("Created context");
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

		m_window = std::make_unique<WindowImpl>(name, windowSize);
		if (!m_window.get()) {
			SDL_Quit();
			throw std::runtime_error(std::string("Failed to create SDL Window: ") + SDL_GetError());
		}

		m_context = std::make_unique<ContextImpl>(*m_window);
		if (!m_context) {
			m_window.reset();
			SDL_Quit();
			throw std::runtime_error(std::string("Failed to create OpenGL context: ") + SDL_GetError());
		}

		if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
			m_context.reset();
			m_window.reset();
			SDL_Quit();
			throw std::runtime_error(std::string("Failed to initialize GLAD"));
		}
		
		/*int* profileMask;
		int* majorVersion;
		int* minorVersion;
		int* stencilSize;

		SDL_GL_GetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, profileMask);
		SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, majorVersion);
		SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minorVersion);
		SDL_GL_GetAttribute(SDL_GL_STENCIL_SIZE, stencilSize);

		Debug::Log(*majorVersion);*/

		int vertexAmount = 4;
		int vertexPositionSize = 3;
		int vertexColorSize = 3;
		int vertexTextureCoordsSize = 2;

		// CPU Buffer
		float vertices[] = {
			// positions       // colors         // texture coords
			0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // top right
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
		   -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom left
		   -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f   // top left
		};
		unsigned int indices[] = {
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
		};

		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);

		// GPU Buffer
		glGenBuffers(1, &m_vbo);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// Index Buffer
		glGenBuffers(1, &m_ebo);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}
	
	Graphics::~Graphics()
	{
		if (m_context)
		{
			m_context.reset();
			Debug::Log("Destroyed Context");

		}

		if (m_window)
		{
			m_window.reset();
			Debug::Log("Destroyed Window");
		}

		Debug::Log("Quit Application");

		glDeleteBuffers(1, &m_vbo);
		glDeleteVertexArrays(1, &m_vao);
		glDeleteBuffers(1, &m_ebo);

		SDL_Quit();

		// 1 m = 32 pixels
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
