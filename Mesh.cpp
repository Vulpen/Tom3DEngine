#include "Mesh.h"

std::vector<std::string>split(std::string s, std::string t)
{
	std::vector<std::string> ret;
	while (1)
	{
		int pos = s.find(t);
		if (pos == -1) {
			ret.push_back(s);
			break;
		}
		ret.push_back(s.substr(0, pos));
		s = s.substr(pos + 1, s.size() - pos - 1);
	}

	return ret;
}

Mesh::Mesh():_isLoaded(false), _vertexBuffer(0),
			 _vertexArray(0), _vertices()
{}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &_vertexArray);
	glDeleteBuffers(1, &_vertexBuffer);
}

void Mesh::Draw() {
    if (!_isLoaded) return;

    glBindVertexArray(_vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    glDrawArrays(GL_TRIANGLES, 0, _vertices.size());
    glBindVertexArray(0);
}

void Mesh::initializeGLBuffers()
{
    glGenBuffers(1, &_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices[0], GL_STATIC_DRAW);

    glGenVertexArrays(1, &_vertexArray);
    glBindVertexArray(_vertexArray);

    //Position attribute
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(0));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(GLfloat) * 3));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(GLfloat) * 6));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

bool Mesh::Load(const std::string& filename)
{
	std::vector<unsigned int> vertexIndices, uvIndices, nrmlIndices;
	std::vector<glm::vec3> tempVertices;
	std::vector<glm::vec3> tempNormals;
	std::vector<glm::vec2> tempUVs;

	//std::ofstream ct;
	//ct.open("garbo.txt", std::ofstream::app);
	//ct << filename;
	//ct.close();

	if (filename.find(".obj") != std::string::npos)
	{
		std::ifstream fin;
		//fin.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		fin.open(filename, std::ios::in);

		if (!fin)
		{
			std::cerr << "Cannot open " << filename << std::endl;
			return false;
		}

		std::cout << "Loading OBJ file " << filename << " ..." << std::endl;

		std::string lineBuffer;
		while (std::getline(fin, lineBuffer))
		{
			std::stringstream ss(lineBuffer);
			std::string cmd;
			ss >> cmd;

			if (cmd == "v")
			{
				glm::vec3 vertex;
				int dim = 0;
				while (dim < 3 && ss >> vertex[dim]) {
					dim += 1;
				}
				tempVertices.push_back(vertex);
			}
			else if (cmd == "vt")
			{
				glm::vec2 uv;
				int dim = 0;
				while (dim < 2 && ss >> uv[dim]) {
					dim += 1;
				}
				tempUVs.push_back(uv);
			}
			else if (cmd == "vn")
			{
				glm::vec3 normal;
				int dim = 0;
				while (dim < 3 && ss >> normal[dim]) {
					dim += 1;
				}
				normal = glm::normalize(normal);
				tempNormals.push_back(normal);
			}
			else if (cmd == "f")
			{
				std::string faceData;
				int vertexIndex, uvIndex, normalIndex;

				while (ss >> faceData)
				{
					std::vector<std::string> data = split(faceData, "/");

					if (data[0].size() > 0)
					{
						sscanf_s(data[0].c_str(), "%d", &vertexIndex);
						vertexIndices.push_back(vertexIndex);
					}

					if (data.size() >= 1) {
						if (data[1].size() > 0) {
							sscanf_s(data[1].c_str(), "%d", &uvIndex);
							uvIndices.push_back(uvIndex);
						}
					}

					if (data.size() >= 2) {
						if (data[2].size() > 0) {
							sscanf_s(data[2].c_str(), "%d", &normalIndex);
							nrmlIndices.push_back(normalIndex);
						}
					}
				}
			}
		}

		// Close the file
		fin.close();


		// For each vertex of each triangle
		for (unsigned int i = 0; i < vertexIndices.size(); i++)
		{
			Vertex meshVertex;

			if (tempVertices.size() > 0)
			{
				glm::vec3 vertex = tempVertices[vertexIndices[i] - 1];
				meshVertex.position = vertex;
			}
			if (tempNormals.size() > 0)
			{
				glm::vec3 nrml = tempNormals[nrmlIndices[i] - 1];
				meshVertex.normal = nrml;
			}
			if (tempUVs.size() > 0)
			{
				glm::vec2 uv = tempUVs[uvIndices[i] - 1];
				meshVertex.texCoord = uv;
			}

			_vertices.push_back(meshVertex);
		}

		// Create and initialize the buffers
		initializeGLBuffers();
		std::cout << "Finished Loading OBJ File" << std::endl;
		return (_isLoaded = true);
	}

	// We shouldn't get here so return failure
	return false;
}