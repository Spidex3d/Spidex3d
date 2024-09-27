#pragma once
#include <glad\glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>
#include "../Shader/Shader.h"

#define MAX_BONE_INFLUENCE 4

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;

	int m_boneIDs[MAX_BONE_INFLUENCE];
	float m_Weight[MAX_BONE_INFLUENCE];
};
struct Texture {
	unsigned int id;
	std::string type;
	std::string path;
};




class Mesh
{
public:
	//mesh data
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	unsigned int VAO;

	// contructor
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,std::vector<Texture> textures)
	{
		this->vertices = vertices;
		this->indices  = indices;
		this->textures = textures;

		setupMesh();
	}

	void Draw(Shader& shader)
	{
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		unsigned int normalNr  = 1;
		unsigned int heightNr  = 1;
		for (unsigned int i = 0; i < textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);

			std::string number;
			std::string name = textures[i].type;
			if (name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = std::to_string(specularNr++); // transfer unsigned int to string
			else if (name == "texture_normal")
				number = std::to_string(normalNr++); // transfer unsigned int to string
			else if (name == "texture_height")
				number = std::to_string(heightNr++); // transfer unsigned int to string
			// now set the sampler to the correct texture unit
			glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
			// and finally bind the texture
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}


	}

private:
	unsigned int VBO, EBO;

	void setupMesh()
	{

	}



};
