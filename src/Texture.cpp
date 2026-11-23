//#include "Texture.h"
//
//#include <iostream>
//
//#include "Graphics.h"
//
//namespace Engineering2D
//{
//	Texture::Texture(Texture&& t) noexcept
//	{
//		m_texture = t.m_texture;
//		t.m_texture = nullptr;
//	}
//
//	Texture& Texture::operator=(Texture&& t) noexcept
//	{
//		m_texture = t.m_texture;
//		t.m_texture = nullptr;
//		
//		return *this;
//	}
//	
//	Texture::Texture(const std::string& filePath)
//	{
//		m_texture = CreateTexture(filePath);
//	}
//
//	Texture::~Texture()
//	{
//		SDL_DestroyTexture(m_texture);
//	}
//	
//	SDL_Texture* Texture::CreateTexture(const std::string& filePath, Graphics& program)
//	{
//		SDL_Surface* surface = SDL_LoadBMP(filePath.c_str());
//		SDL_SetSurfaceColorKey(surface, true, SDL_MapSurfaceRGB(surface, 255, 0, 255));
//
//		if (surface == nullptr) {
//			std::cout << "Error loading surface: " << *SDL_GetError() << std::endl;
//		}
//		else {
//			m_texture = SDL_CreateTextureFromSurface(program.GetRenderer(), surface);
//			if (m_texture == nullptr) {
//				std::cout << "Error creating texture: " << *SDL_GetError() << std::endl;
//			}
//			else {
//				SDL_SetTextureScaleMode(m_texture, SDL_SCALEMODE_PIXELART);
//			}
//		}
//
//		SDL_DestroySurface(surface);
//		
//		return m_texture;
//	}
//}
