#pragma once
#include "GL/glew.h"

enum ImageFormat {
	PNG = 0,
	JPG = 1,
};

class Texture {
public:
	Texture(int activeTexture, int width, int height, unsigned char* data, ImageFormat imageFormat);
	~Texture();
	void Bind();
	void Unbind();
private:
	unsigned int m_TextureId;
	GLenum GetFormat(ImageFormat imageFormat);
};
