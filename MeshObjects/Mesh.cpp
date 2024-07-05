//#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include "Mesh.h"
#include "../Shader/Shader.h"
#include "../src/Textures.h"



Mesh* Mesh::Instance()
{
	static Mesh* Tmesh = new Mesh;

	return Tmesh;
	
}

bool Mesh::Initialize()
{
	Shader defaultShader;
	defaultShader.Load("Shader/shaderFile/default.vert", "Shader/shaderFile/default.frag");
	
	//##################### Texture Test ####################
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//#########################################
	
	//location = 0 attribute 3 vertices        strid 8				start at 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// colour location = 1
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// Texture location 2
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	
	// flip image
	stbi_set_flip_vertically_on_load(true);

	int width, height, nrChannels;
	
	std::string texPath = "Textures/";
	std::string texImg = "github.jpg";

	unsigned int defaultMap = loadTexture((texPath + texImg).c_str());
	
	
	defaultShader.Use();
		
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, defaultMap);

	glBindVertexArray(VAO);
	
	Mesh::DrawTriangel();
	

	defaultShader.Destroy();

	return true;
}

void Mesh::DrawTriangel()
{
	
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	
}
