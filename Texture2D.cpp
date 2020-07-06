#include "Texture2D.h"

Texture2D::Texture2D()
	:_textureID(0), _width(0), _height(0)
{}

bool Texture2D::loadTexture(const string& filename, bool generateMipMamps = true)
{
	int components;

	unsigned char* imageData = stbi_load(filename.c_str(), &_width, &_height, &components, STBI_rgb_alpha);

	if (imageData == NULL) {
		std::cerr << "Error loading texture: " << filename << std::endl;
		return false;
	}

	//Flip Texture
	int widthInBytes = _width * 4;
	unsigned char* top = NULL;
	unsigned char* bottom = NULL;
	unsigned char temp = 0;
	int halfHeight = _height / 2;
	for (int row = 0; row < halfHeight; row++) {
		top = imageData + row * widthInBytes;
		bottom = imageData + (_height - row - 1) * widthInBytes;
		for (int col = 0; col < widthInBytes; col++) {
			temp = *top;
			*top = *bottom;
			*bottom = temp;
			top++;
			bottom++;
		}
	}

	glGenTextures(1, &_textureID);
	glBindTexture(GL_TEXTURE_2D, _textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Render surface smaller than texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Render surface larger

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	if (generateMipMamps)
		glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(imageData);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::bind(GLuint texUnit) {
	glActiveTexture(GL_TEXTURE0 + texUnit);
	glBindTexture(GL_TEXTURE_2D, _textureID);
}

void Texture2D::unbind(GLuint texUnit = 0)
{
	glActiveTexture(GL_TEXTURE0 + texUnit);
	glBindTexture(GL_TEXTURE_2D, 0);
}