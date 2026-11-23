#include "TextureManager.h"
#include "Graphics.h"

#include <SDL3/SDL.h>
#include <glad/glad.h>

#include "Scene.h"
#include "stb_image.h"

namespace Engineering2D
{
	TextureManager::~TextureManager()
	{
		for (auto i = textures.begin(); i!= textures.end(); ++i)
		{
			textures.erase(i);
		}
	}

	std::shared_ptr<Texture> TextureManager::GetTexture(char const* filePath)
	{
		if (auto it = textures.find(filePath); it != textures.end())
		{
			std::cout << "Loaded texture: " << filePath << std::endl;
			return it->second;
		}

		auto texture = std::make_shared<Texture>(filePath);
		textures[filePath] = texture;

		std::cout << "Created texture: " << filePath << std::endl;
		return texture;
	}

	unsigned int TextureManager::GenerateTexture(const char* filePath)
	{
		GLuint texture;
		glGenTextures(1, &texture);
		glActiveTexture(GL_TEXTURE0 + textures.size());
		glBindTexture(GL_TEXTURE_2D, texture);

		// Set texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height, nrChannels;
		unsigned char* data = stbi_load(filePath, &width, &height,
			&nrChannels, 0);
		if (data) {

			GLenum format = nrChannels == 4 ? GL_RGBA : GL_RGB;

			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
				GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			std::cout << "Failed to load texture '" << filePath << "' " << stbi_failure_reason() << std::endl;
			glDeleteTextures(1, &texture);
			return 0;
		}

		stbi_image_free(data);

		return texture;
	}

	//===========================================================================

	Texture::Texture(Texture&& t) noexcept
	{
		m_textureIndex = t.m_textureIndex;
	}

	Texture& Texture::operator=(Texture&& t) noexcept
	{
		m_textureIndex = t.m_textureIndex;

		return *this;
	}

	Texture::Texture(unsigned int textureIndex) : m_textureIndex(textureIndex)
	{
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_textureIndex);
	}
}
