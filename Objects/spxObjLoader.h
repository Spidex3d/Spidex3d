#pragma once
#include <glad\glad.h>
#include <vector>
#include <string>
#include <glm\glm.hpp>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

class spxObjLoader
{

public:
	spxObjLoader();
	~spxObjLoader();

	bool loadOBJ(const std::string& filename);
	void objDraw();

private:
	void initBuffers();

	bool m_Loaded;
	std::vector<Vertex> m_Vertices;
	GLuint m_VBO, m_VAO;

};

