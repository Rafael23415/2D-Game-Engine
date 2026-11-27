#pragma once

#include <memory>
#include <string>

#include <SDL3/SDL.h>
#include <glad/glad.h>

#include "Vector2D.h"
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
		
		unsigned int transLoc;
		
		unsigned int m_shaderProgram;
		
		unsigned int CompileShader(GLenum type, const std::string& shaderSource);
		unsigned int CreateShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource);
		
	public:
		Graphics(const char* title, const Math::Vector2DInt windowSize);
		~Graphics();
		
		void ClearContext() const;
		void Render(const Math::Vector2D& position) const;
		void SwapWindow() const;
	};
}
