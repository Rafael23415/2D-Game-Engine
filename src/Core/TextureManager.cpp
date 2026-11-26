#include "TextureManager.h"

#include <glad/glad.h>

#include "stb_image.h"
#include "Debug.h"

namespace Engineering2D
{
	Texture::Texture(unsigned int textureIndex) : m_textureIndex(textureIndex)
	{
		Debug::Log("Texture created");
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_textureIndex);
		Debug::Log("Texture destroyed");
	}

	//===========================================================================

	std::shared_ptr<Texture> TextureManager::GetTexture(const char* filePath)
	{
		if (auto it = m_textures.find(filePath); it != m_textures.end())
		{
			Debug::Log("Loaded texture: ", filePath);
			return it->second;
		}

		unsigned int texture;

		if (GenerateTexture(filePath, texture))
		{
			auto p_texture = std::make_shared<Texture>(texture);
			m_textures[filePath] = p_texture;

			Debug::Log("Created texture: ", filePath);

			return p_texture;
		}
		else
		{
			return 0;
		}
	}

	bool TextureManager::GenerateTexture(const char* filePath, unsigned int& texture)
	{
		GLuint t;
		glGenTextures(1, &t);
		glActiveTexture(GL_TEXTURE0 + m_textures.size());
		glBindTexture(GL_TEXTURE_2D, t);

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
			glDeleteTextures(1, &t);
			return false;
		}

		stbi_image_free(data);

		texture = t;

		return true;
	}
}
