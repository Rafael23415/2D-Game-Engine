#include "SpriteSheet.h"

#include <iostream>

#include "Program.h"

namespace Engineering2D
{
	SpriteSheet::SpriteSheet(SpriteSheet&& t) noexcept
	{
		spriteSheet = t.spriteSheet;
		t.spriteSheet = nullptr;
	}

	SpriteSheet& SpriteSheet::operator=(SpriteSheet&& t) noexcept
	{
		spriteSheet = t.spriteSheet;
		t.spriteSheet = nullptr;
		
		return *this;
	}
	
	SpriteSheet::SpriteSheet(const std::string& filePath)
	{
		spriteSheet = CreateTexture(filePath);
	}

	SpriteSheet::~SpriteSheet()
	{
		SDL_DestroyTexture(spriteSheet);
	}

	SDL_Texture* SpriteSheet::CreateTexture(const std::string& filePath, Program& program)
	{
		SDL_Surface* surface = SDL_LoadBMP(filePath.c_str());
		SDL_SetSurfaceColorKey(surface, true, SDL_MapSurfaceRGB(surface, 255, 0, 255));

		if (surface == nullptr) {
			std::cout << "Error loading surface: " << *SDL_GetError() << std::endl;
		}
		else {
			spriteSheet = SDL_CreateTextureFromSurface(program.GetRenderer(), surface);
			if (spriteSheet == nullptr) {
				std::cout << "Error creating texture: " << *SDL_GetError() << std::endl;
			}
			else {
				SDL_SetTextureScaleMode(spriteSheet, SDL_SCALEMODE_PIXELART);
			}
		}

		SDL_DestroySurface(surface);
		
		return spriteSheet;
	}
}
