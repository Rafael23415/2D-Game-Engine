#pragma once

#include <memory>
#include <string>

#include <SDL3/SDL.h>
#include <glad/glad.h>
#include "Vector2DInt.h"

namespace Engineering2D
{
	/**
	 * 
	 */
	class Graphics
	{
	private:
		struct WindowImpl;
		struct ContextImpl;
		
		std::unique_ptr<WindowImpl> m_window;
		std::unique_ptr<ContextImpl> m_context;

		unsigned int m_vbo;
		unsigned int m_vao;
		unsigned int m_ebo;

		unsigned int m_shaderProgram;

	public:
		Graphics(const char* title, const Math::Vector2DInt windowSize);
		~Graphics();

		unsigned int CompileShader(GLenum type, const std::string& shaderSource);
		unsigned int CreateShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource);

		void ClearContext();
		void Render();
		void SwapWindow();
	};
}
