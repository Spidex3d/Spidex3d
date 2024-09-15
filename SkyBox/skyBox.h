#pragma once
#include <glad\glad.h>
//#include <stb\stb_image.h>
#include <iostream>
#include "skyMesh.h"
#include <vector>

// ###################### My Sky box ######################
unsigned int skyVAO, skyVBO, skyEBO;
unsigned int skyTextureID;

void SkyBox() {
	glGenVertexArrays(1, &skyVAO);
	glGenBuffers(1, &skyVBO);
	glGenBuffers(1, &skyEBO);
	glBindVertexArray(skyVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SkyBoxVert), &SkyBoxVert, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxInds), &skyboxInds, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	std::string skyPath = "Textures/";
	std::string skyMap[6] =
	{
		skyPath + "skybox/right.jpg",
		skyPath + "skybox/left.jpg",
		skyPath + "skybox/top.jpg",
		skyPath + "skybox/bottom.jpg",
		skyPath + "skybox/front.jpg",
		skyPath + "skybox/back.jpg"

	};

	// Creat a cubemap for the skybox

	glGenTextures(1, &skyTextureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyTextureID);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// this stuff is important to prevent seames
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	 glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	//Cycles through all textures and fix them to the cubemap object
	for (unsigned int i = 0; i < 6; i++)
	{
		int width, height, nrChannels;
		unsigned char* data = stbi_load(skyMap[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			stbi_set_flip_vertically_on_load(false);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
				GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

			stbi_image_free(data);
		}
		else
		{
			std::cout << "Failed to load texture: " << skyMap[i] << std::endl;
			stbi_image_free(data);
		}
	}
	
}
