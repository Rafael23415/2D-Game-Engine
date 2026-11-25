#pragma once

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

	public:
		Graphics(const char* title, const Math::Vector2DInt windowSize);
		
		~Graphics();

		void ClearContext();
		void SwapWindow();
	};
}
