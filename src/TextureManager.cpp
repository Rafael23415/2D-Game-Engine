#include "TextureManager.h"

#include <SDL3/SDL.h>
#include <glad/glad.h>

#include "stb_image.h"
#include "Graphics.h"
#include "Debug.h"
#include "Scene.h"

namespace Engineering2D
{
	Texture::Texture(unsigned int textureIndex) : m_textureIndex(textureIndex)
	{
		Debug::Log("Created a texture");
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_textureIndex);
		Debug::Log("Destroyed a texture");
	}

	//===========================================================================

	std::shared_ptr<Texture> TextureManager::GetTexture(char const* filePath)
	{
		if (auto it = m_textures.find(filePath); it != m_textures.end())
		{
			Debug::Log("Loaded texture: ", filePath);
			return it->second;
		}

		auto texture = std::make_shared<Texture>(GenerateTexture(filePath));
		m_textures[filePath] = texture;

		Debug::Log("Created texture: ", filePath);
		return texture;
	}

	unsigned int TextureManager::GenerateTexture(const char* filePath)
	{
		GLuint texture;
		glGenTextures(1, &texture);
		glActiveTexture(GL_TEXTURE0 + m_textures.size());
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
			Debug::LogWarning("Failed to load texture '", filePath, "' ", stbi_failure_reason());
			glDeleteTextures(1, &texture);
			return 0;
		}

		stbi_image_free(data);

		return texture;
	}
}
