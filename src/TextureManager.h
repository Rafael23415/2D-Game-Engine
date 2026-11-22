#pragma once

#include <map>
#include <string>

#include "SpriteSheet.h"

namespace Engineering2D
{
	class TextureManager
	{
	public:
		TextureManager() = default;
		~TextureManager();

		SpriteSheet* CreateTexture(const std::string& textureFilePath);
		
	private:
		std::map<const std::string, SpriteSheet*> spriteSheets;
	};
}
