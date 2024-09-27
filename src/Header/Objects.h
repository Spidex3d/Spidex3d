#pragma once
#include <glad\glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

struct Object3d {

	GLuint vao;
	GLuint vbo;
	GLuint ebo;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	std::vector<float> vertices;
	std::vector<unsigned int> indices;

};

void initializeObject(Object3d& object) {

	glGenVertexArrays(1, &object.vao);
	glGenBuffers(1, &object.vbo);
	glGenBuffers(1, &object.ebo);

	glBindVertexArray(object.vao);

	glBindBuffer(GL_ARRAY_BUFFER, object.vbo);
	glBufferData(GL_ARRAY_BUFFER, object.vertices.size() * sizeof(float), object.vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, object.indices.size() * sizeof(unsigned int), object.indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);


	}
	