#pragma once
#include <string>
#include <iostream>
#include "GL/glew.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb-master/stb_image.h"

using std::string;

class Texture2D
{
public:
	Texture2D();
	
	bool loadTexture(const string& filename, bool generateMipMamps = true);
	void bind(GLuint texUnit = 0);
	void unbind(GLuint texUnit = 0);

private:
	GLuint _textureID;
	int _width;
	int _height;
};

