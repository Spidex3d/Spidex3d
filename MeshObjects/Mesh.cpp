#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include "Mesh.h"
#include "../Shader/Shader.h"



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
	// put the buffer stuff in here
	//unsigned int buffer;
	//glGenBuffers(1, &buffer);
	//glBindBuffer(GL_ARRAY_BUFFER, buffer);

	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//location = 0 attribute 3 vertices        strid 6				start at 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// colour location = 1
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// Texture location 2
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// ******************************
	
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	
	stbi_set_flip_vertically_on_load(true);

	int width, height, nrChannels;
	
	std::string texPath = "Textures/";
	std::string texImg = "github.jpg";
	
	unsigned char* data = stbi_load((texPath + texImg).c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	//*******************************
	
	

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindBuffer(GL_ARRAY_BUFFER, 1);

	//glBindVertexArray(0);
	//glBindVertexArray(1);

	//glBindTexture(GL_TEXTURE_2D, texture);
	defaultShader.Use();
	//glBindVertexArray(VAO);
	
	glBindVertexArray(VAO);
	//Mesh::DrawTriangel();

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	defaultShader.Destroy();

	return true;
}

void Mesh::DrawTriangel()
{
	
	// GL Draw Triangel
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	
}
