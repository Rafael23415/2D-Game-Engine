#pragma once

#include "Vector2DInt.h"
#include "TextureManager.h"

namespace Engineering2D
{
	using namespace Math;

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

	public:
		Graphics(const char* title, const Vector2DInt windowSize);
		
		~Graphics();

		void ClearContext();
		void SwapWindow();
	};
}
