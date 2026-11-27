#include "Graphics.h"

#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdexcept>

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

		WindowImpl(const char* title, const Vector2DInt windowSize) : m_windowPtr(SDL_CreateWindow(title, windowSize.x, windowSize.y, SDL_WINDOW_OPENGL), SDL_DestroyWindow)
		{
			if (!m_windowPtr)
			{
				throw std::runtime_error(std::string("Failed to create SDL Window: ") + SDL_GetError());
			}

			Debug::Log("Created window: ", title, " | ", windowSize);
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

		ContextImpl(const WindowImpl& window)
		{
			m_contextPtr = SDL_GL_CreateContext(window.m_windowPtr.get());

			if (!m_contextPtr)
			{
				throw std::runtime_error(std::string("Failed to create OpenGL context: ") + SDL_GetError());
			}

			Debug::Log("Created context");
		}
		
		~ContextImpl()
		{
			SDL_GL_DestroyContext(m_contextPtr);
		}
	};

	// ---------------------------------------------------------
	// Graphics
	// ---------------------------------------------------------

	unsigned int Graphics::CompileShader(GLenum type, const std::string& shaderSource)
	{
		GLuint shader = glCreateShader(type);
		const char* source = shaderSource.c_str();
		glShaderSource(shader, 1, &source, NULL);
		glCompileShader(shader);

		GLint success;
		char infoLog[512];

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::" << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") << "::COMPILATION_FAILED\n" << infoLog << std::endl;
			glDeleteShader(shader);
			return 0;
		}

		return shader;
	}

	unsigned int Graphics::CreateShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource)
	{
		/*
		 * Shader called for every vertex.
		 * Tells OpenGL where the vertex will be, it's color and the texture coordinates.
		 */
		GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
		
		/*
		 * Called for each pixel that's inside the triangle, filling it.
		 * Decides the color of the pixel.
		 */
		GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
		
		if (!vertexShader || !fragmentShader)
		{
			Debug::LogError("Failed creating shaders!");

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
			return 0;
		}

		// Create program
		GLuint shaderProgram = glCreateProgram();

		// Attach shaders and link
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		// Clean up individual shaders
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		GLint success;
		char infoLog[512];

		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
			glDeleteProgram(shaderProgram);

			return 0;
		}

		return shaderProgram;
	}

	Graphics::Graphics(const char* title, const Vector2DInt windowSize)
	{
		if (!SDL_Init(SDL_INIT_VIDEO)) {
			throw std::runtime_error(std::string("SDL_Init failed: ") + SDL_GetError());
		}

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

		int profileMask;
		int majorVersion;
		int minorVersion;
		
		SDL_GL_GetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, &profileMask);
		SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &majorVersion);
		SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minorVersion);
		
		Debug::Log((profileMask == 1 ? "OpenGL Core Profile" : (profileMask == 2 ? "OpenGL Compatibility Profile" : "GLX_CONTEXT_ES2_PROFILE_BIT_EXT")), " | Version ", majorVersion, ".", minorVersion);

		m_window = std::make_unique<WindowImpl>(title, windowSize);
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
		
		// Vertex attributes
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
		
		const char* vertexShaderSource = R"glsl(
#version 330 core

in vec3 position;
in vec3 color;

out vec3 Color;

uniform mat4 transform;

void main()
{
    Color = color;
    gl_Position = transform * vec4(position, 1.0);
}
)glsl";

		const char* fragmentShaderSource = R"glsl(
#version 330 core
in vec3 Color;

out vec4 outColor;

void main()
{
    outColor = vec4(Color, 1.0);
}
)glsl";
		
		m_shaderProgram = CreateShaderProgram(vertexShaderSource, fragmentShaderSource);

		if (!m_shaderProgram)
		{
			throw std::runtime_error("Failed creating program!");
		}
		
		glUseProgram(m_shaderProgram);
		
		GLuint posAttrib = glGetAttribLocation(m_shaderProgram, "position");
		glEnableVertexAttribArray(posAttrib);
		glVertexAttribPointer(posAttrib, vertexPositionSize, GL_FLOAT, GL_FALSE,
			sizeof(vertices) / vertexAmount, 0);
		
		GLuint colAttrib = glGetAttribLocation(m_shaderProgram, "color");
		glEnableVertexAttribArray(colAttrib);
		glVertexAttribPointer(colAttrib, vertexColorSize, GL_FLOAT, GL_FALSE,
			sizeof(vertices) / vertexAmount, (void*)(vertexPositionSize * sizeof(float)));
		
		transLoc = glGetUniformLocation(m_shaderProgram, "transform");
		
		// Unbind VAO
		glBindVertexArray(0);
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
		glDeleteProgram(m_shaderProgram);

		SDL_Quit();

		// 1 m = 32 pixels
	}

	void Graphics::ClearContext() const
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	
	void Graphics::Render(const Vector2D& position) const
	{
		auto trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(position.x, position.y, 0));
		
		glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(trans));
		
		glBindVertexArray(m_vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);
	}
	
	void Graphics::SwapWindow() const
	{
		if(m_window)
		{
			m_window->SwapWindow();
		}
	}
}
