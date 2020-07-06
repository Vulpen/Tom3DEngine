#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <direct.h>

#include "GL/glew.h"
#include "glm/glm.hpp"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
};

class Mesh
{
public:
	Mesh();
	~Mesh();


	bool Load(const std::string& filename);
	void Draw();

private:
	void initializeGLBuffers();
	bool _isLoaded;
	std::vector<Vertex> _vertices;
	GLuint _vertexBuffer;
	GLuint _vertexArray;
};

