#pragma once

#include <string>
#include <unordered_map>
#include <memory>

#include "Vector2D.h"
#include "Vector2DInt.h"

namespace Engineering2D
{
	class Texture
	{
	public:
		Texture(unsigned int textureIndex);

		~Texture();

	private:
		unsigned int m_textureIndex;

		// SDL_FRect spritePositionScale;
		// SDL_FRect spriteCrop;
		//
		// Vector2D textureSize;
		// Vector2DInt frameSize;
		//
		// const float frame_duration = 0;
		// float frameTime = 0;
	};
	
	//===========================================================================

	class TextureManager
	{
	public:
		TextureManager() = default;
		~TextureManager() = default;

		std::shared_ptr<Texture> GetTexture(char const* filePath);

	private:
		std::unordered_map<std::string, std::shared_ptr<Texture>> m_textures;

		unsigned int GenerateTexture(char const* filePath);
	};
}
