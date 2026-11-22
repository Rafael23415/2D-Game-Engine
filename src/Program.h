#pragma once

#include "SpriteSheet.h"
#include "Vector2DInt.h"

namespace Engineering2D
{
	/**
	 * 
	 */
	class Program
	{
	private:
		class WindowImpl;
		class RendererImpl;
		
		std::unique_ptr<WindowImpl> window;
		std::unique_ptr<RendererImpl> renderer;

	public:
		Program(const char* title, const Vector2DInt windowSize);
		Program() = default;
		
		// Forbid copy
		Program(const Program& a) = delete;
		Program& operator=(const Program& a) = delete;
		
		// Allow move
		Program(Program&& a) noexcept;
		Program& operator=(Program&& a) noexcept; 
		
		~Program();
		
		WindowImpl* GetWindow() const;
		RendererImpl* GetRenderer() const;

		void SetVSync(bool enabled) const;

		void SetColor(Uint8 r, Uint8 g, Uint8 b) const;
		void ClearRenderer() const;
		void RenderTexture(SpriteSheet& spriteSheet);
		void PresentRenderer() const;
	};
}
