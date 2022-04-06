#include "Texture.h"

Texture::Texture(int activeTexture, int width, int height, unsigned char* data, ImageFormat imageFormat)
{
	glActiveTexture(GL_TEXTURE0 + activeTexture);
	glGenTextures(1, &m_TextureId);
	glBindTexture(GL_TEXTURE_2D, m_TextureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GetFormat(imageFormat), GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_TextureId);
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_TextureId);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLenum Texture::GetFormat(ImageFormat imageFormat)
{
	switch (imageFormat) {
		case ImageFormat::PNG:
			return GL_RGBA;
		case ImageFormat::JPG:
			return GL_RGB;
		default:
			return GL_RGB;
	};
}
