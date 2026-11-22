#include "Program.h"

#include <SDL3/SDL.h>

#include <iostream>
#include <stdexcept>
#include <string>


namespace Engineering2D
{
	//using namespace Math;

	// ======================================================================================

	class Program::WindowImpl {
	
	public:
		WindowImpl(const char* title, const Vector2DInt windowSize) {
			window = SDL_CreateWindow(title, windowSize.x, windowSize.y, 0);
			if (!window) {
				throw std::runtime_error(std::string("Failed to create SDL Window: ") + SDL_GetError());
			}
		}

		~WindowImpl()
		{
			SDL_DestroyWindow(window);
		}

		SDL_Window* GetWindow() const
		{
			return window;
		}
		
	private:
		SDL_Window* window;
	};
	
	// ======================================================================================

	class Program::RendererImpl {
		
	public:
		RendererImpl(const WindowImpl& window)
		{
			renderer = SDL_CreateRenderer(window.GetWindow(), nullptr);
			if (!renderer) {
				throw std::runtime_error(std::string("Failed to create OpenGL context: ") + SDL_GetError());
			}
		}

		~RendererImpl()
		{
			SDL_DestroyRenderer(renderer);
		}
		
		SDL_Renderer* GetRenderer() const
		{
			return renderer;
		}
		
	private:
		SDL_Renderer* renderer;
	};

	// ======================================================================================

	Program::Program(const char* name, const Vector2DInt windowSize)
	{
		if (!SDL_Init(SDL_INIT_VIDEO)) {
			throw std::runtime_error(std::string("SDL_Init failed: ") + SDL_GetError());
		}
		
		window = std::make_unique<WindowImpl>(name, windowSize);
		renderer = std::make_unique<RendererImpl>(*window);
	}
	
	Program::Program(Program&& a) noexcept
	{
		renderer = std::move(a.renderer);
		window = std::move(a.window);
		
		a.renderer = nullptr;
		a.window = nullptr;
	}
	
	Program& Program::operator=(Program&& a) noexcept
	{
		if (this != &a)
		{
			if (a.renderer)
			{
				renderer.reset();
				renderer = std::move(a.renderer);
				a.renderer = nullptr;
			}
			
			if (a.window)
			{
				window.reset();
				window = std::move(a.window);
				a.window = nullptr;
			}
			
		}
		return *this;
	}
	
	Program::~Program()
	{
		if (renderer)
		{
			renderer.reset();
		}
		
		if (window)
		{
			window.reset();
		}
		
		SDL_Quit();
	}
	
	Program::WindowImpl* Program::GetWindow() const
	{
		if (!window)
		{
			std::cout << "Window not found!" << std::endl;
		}
		
		return window.get();
	}

	Program::RendererImpl* Program::GetRenderer() const
	{
		if (!renderer)
		{
			std::cout << "Renderer not found!" << std::endl;
		}
		
		return renderer.get();
	}

	void Program::SetVSync(bool enabled) const
	{
		SDL_SetRenderVSync(renderer->GetRenderer(), enabled);
	}

	void Program::SetColor(Uint8 r, Uint8 g, Uint8 b) const
	{
		SDL_SetRenderDrawColor(renderer->GetRenderer(), r, g, b, 255);
	}

	void Program::ClearRenderer() const
	{
		SDL_RenderClear(renderer->GetRenderer());
	}

	void Program::RenderTexture(SpriteSheet& spriteSheet)
	{
		//SDL_RenderTexture(renderer, texture.Get(), texture.GetNeedCrop() ? &texture.GetSpriteCrop() : nullptr, &texture.GetSpritePositionScale());
	}

	void Program::PresentRenderer() const
	{
		SDL_RenderPresent(renderer->GetRenderer());
	}
}
