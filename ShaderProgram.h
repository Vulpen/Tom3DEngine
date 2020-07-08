#pragma once

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>

using std::string;
class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();

	enum ShaderType
	{
		VERTEX,
		FRAGMENT,
		PROGRAM
	};

	/// <summary>
	/// Loads and Compiles Vertex and Fragment shaders.
	/// </summary>
	bool loadShaders(const char* vsFilename, const char* fsFilename);
	void use();
	void setUniform(const GLchar* name, const glm::vec2& v);
	void setUniform(const GLchar* name, const glm::vec3& v);
	void setUniform(const GLchar* name, const glm::vec4& v);
	void setUniform(const GLchar* name, const glm::mat4& m);
	void setUniform(const GLchar* name, const GLfloat& f);
	void setUniformSampler(const GLchar* name, const GLint& slot);

	GLuint getProgram()const;
private:
	string fileToString(const string& filename);
	void checkCompileErrors(GLuint shader, ShaderType type);
	GLint getUniformLocation(const GLchar* name);

	GLuint mHandle;
	std::map<string, GLint> mUniformLocations;
};

