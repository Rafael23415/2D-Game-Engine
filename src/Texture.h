//#pragma once
//
//#include <SDL3/SDL.h>
//#include <string>
//
//#include "Vector2D.h"
//#include "Vector2DInt.h"
//
//namespace Engineering2D
//{
//	using namespace Math;
//	
//	/**
//	 * @param filePath Path for the image for the texture
//	 */
//	class Texture
//	{
//	public:
//		
//		Texture(const Texture& t) = delete;
//		Texture& operator=(const Texture& t) = delete;
//		
//		Texture(Texture&& t) noexcept;
//		Texture& operator=(Texture&& t) noexcept;
//		
//		Texture(const std::string& filePath);
//		
//		~Texture();
//	
//	private:
//		SDL_Texture* CreateTexture(const std::string& filePath);
//		SDL_Texture* m_texture = nullptr;
//		
//		// SDL_FRect spritePositionScale;
//		// SDL_FRect spriteCrop;
//		//
//		// Vector2D textureSize;
//		// Vector2DInt frameSize;
//		//
//		// const float frame_duration = 0;
//		// float frameTime = 0;
//	};
//}
