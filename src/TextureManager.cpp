#include "TextureManager.h"

#include "Program.h"

namespace Engineering2D
{
	TextureManager::~TextureManager()
	{
		for (auto i = spriteSheets.begin(); i!= spriteSheets.end(); ++i)
		{
			spriteSheets.erase(i);
		}
	}
	
	SpriteSheet* TextureManager::CreateTexture(const std::string& textureFilePath)
	{
		SpriteSheet* spriteSheet = nullptr;
		
		if (spriteSheets.contains(textureFilePath))
		{
			spriteSheet = spriteSheets.at(textureFilePath);
			std::cout << "Texture loaded" << std::endl;
		}
		else
		{
			spriteSheet = new SpriteSheet{textureFilePath};
			spriteSheets[textureFilePath] = spriteSheet;
			std::cout << "Texture created" << std::endl;
		}
		
		return spriteSheet;
	}
}
