#pragma once

#include <SDL3/SDL.h>
#include <string>

#include "Vector2D.h"
#include "Vector2DInt.h"

namespace Engineering2D
{
	using namespace Math;
	
	/**
	 * @param filePath Path for the image for the texture
	 */
	class SpriteSheet
	{
	public:
		
		SpriteSheet(const SpriteSheet& t) = delete;
		SpriteSheet& operator=(const SpriteSheet& t) = delete;
		
		SpriteSheet(SpriteSheet&& t) noexcept;
		SpriteSheet& operator=(SpriteSheet&& t) noexcept;
		
		SpriteSheet(const std::string& filePath);
		
		~SpriteSheet();
	
	private:
		SDL_Texture* CreateTexture(const std::string& filePath);
		SDL_Texture* spriteSheet = nullptr;
		
		// SDL_FRect spritePositionScale;
		// SDL_FRect spriteCrop;
		//
		// Vector2D textureSize;
		// Vector2DInt frameSize;
		//
		// const float frame_duration = 0;
		// float frameTime = 0;
	};
}
