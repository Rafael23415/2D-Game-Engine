#pragma once

#include <string>
#include <unordered_map>
#include <memory>

#include "Vector2D.h"
#include "Vector2DInt.h"

namespace Engineering2D
{
	class TextureManager
	{
	public:
		TextureManager() = default;
		~TextureManager();

		std::shared_ptr<Texture> GetTexture(char const* filePath);

		unsigned int GenerateTexture(char const* filePath);
		
	private:
		std::unordered_map<const std::string, std::shared_ptr<Texture>> textures;
	};

	//===========================================================================

	class Texture
	{
	public:

		Texture(const Texture& t) = delete;
		Texture& operator=(const Texture& t) = delete;

		Texture(Texture&& t) noexcept;
		Texture& operator=(Texture&& t) noexcept;

		Texture(unsigned int textureIndex);

		~Texture();

	private:
		unsigned int m_textureIndex;

		//struct TextureImpl;
		//TextureImpl* m_textureImpl;

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
