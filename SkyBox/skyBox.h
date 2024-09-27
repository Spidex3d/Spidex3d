#pragma once
#include <glad\glad.h>
//#include <stb\stb_image.h>
#include <iostream>
#include "skyMesh.h"
#include <vector>

// ###################### My Sky box ######################
unsigned int skyVAO, skyVBO, skyEBO;
unsigned int skyTextureID;

struct SkyboxSet {
	std::vector<std::string> images; // a vector filled with vector
};

struct SkyData {
	std::string name;
	int LightId;
};

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

}

	/*std::string skyPath = "Textures/skybox/";
	std::string skyMap[6] =
	{
		skyPath + "BlueSky_2/right.jpg",
		skyPath + "BlueSky_2/left.jpg",
		skyPath + "BlueSky_2/top.jpg",
		skyPath + "BlueSky_2/bottom.jpg",
		skyPath + "BlueSky_2/front.jpg",
		skyPath + "BlueSky_2/back.jpg"
	};*/

	std::vector<SkyboxSet> skyboxSets = {
	{{"Textures/skybox/BlueSky/right.jpg", "Textures/skybox/BlueSky/left.jpg", "Textures/skybox/BlueSky/top.jpg", "Textures/skybox/BlueSky/bottom.jpg", "Textures/skybox/BlueSky/front.jpg", "Textures/skybox/BlueSky/back.jpg"}},
	{{"Textures/skybox/BlueSky_2/right.jpg", "Textures/skybox/BlueSky_2/left.jpg", "Textures/skybox/BlueSky_2/top.jpg", "Textures/skybox/BlueSky_2/bottom.jpg", "Textures/skybox/BlueSky_2/front.jpg", "Textures/skybox/BlueSky_2/back.jpg"}},
	{{"Textures/skybox/DarkSky/right.jpg", "Textures/skybox/DarkSky/left.jpg", "Textures/skybox/DarkSky/top.jpg", "Textures/skybox/DarkSky/bottom.jpg", "Textures/skybox/DarkSky/front.jpg", "Textures/skybox/DarkSky/back.jpg"}},
	{{"Textures/skybox/RedSky/right.jpg", "Textures/skybox/RedSky/left.jpg", "Textures/skybox/RedSky/top.jpg", "Textures/skybox/RedSky/bottom.jpg", "Textures/skybox/RedSky/front.jpg", "Textures/skybox/RedSky/back.jpg"}},
	{{"Textures/skybox/MistySky/right.jpg", "Textures/skybox/MistySky/left.jpg", "Textures/skybox/MistySky/top.jpg", "Textures/skybox/MistySky/bottom.jpg", "Textures/skybox/MistySky/front.jpg", "Textures/skybox/MistySky/back.jpg"}},
	{{"Textures/skybox/MistyBlueSky/right.jpg", "Textures/skybox/MistyBlueSky/left.jpg", "Textures/skybox/MistyBlueSky/top.jpg", "Textures/skybox/MistyBlueSky/bottom.jpg", "Textures/skybox/MistyBlueSky/front.jpg", "Textures/skybox/MistyBlueSky/back.jpg"}},
	{{"Textures/skybox/GreenSky/right.jpg", "Textures/skybox/GreenSky/left.jpg", "Textures/skybox/GreenSky/top.jpg", "Textures/skybox/GreenSky/bottom.jpg", "Textures/skybox/GreenSky/front.jpg", "Textures/skybox/GreenSky/back.jpg"}},
	{{"Textures/skybox/NightSky/right.jpg", "Textures/skybox/NightSky/left.jpg", "Textures/skybox/NightSky/top.jpg", "Textures/skybox/NightSky/bottom.jpg", "Textures/skybox/NightSky/front.jpg", "Textures/skybox/NightSky/back.jpg"}},
	{{"Textures/skybox/SifiSky/right.jpg", "Textures/skybox/SifiSky/left.jpg", "Textures/skybox/SifiSky/top.jpg", "Textures/skybox/SifiSky/bottom.jpg", "Textures/skybox/SifiSky/front.jpg", "Textures/skybox/SifiSky/back.jpg"}}
	};


	GLuint LoadSkybox(const SkyboxSet & skyboxSet) {

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
			//unsigned char* data = stbi_load(skyMap[i].c_str(), &width, &height, &nrChannels, 0);
			unsigned char* data = stbi_load(skyboxSet.images[i].c_str(), &width, &height, &nrChannels, 0);
			if (data)
			{
				stbi_set_flip_vertically_on_load(false);
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
					GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

				stbi_image_free(data);
			}
			else
			{
				std::cout << "Failed to load texture: " << skyboxSet.images[i] << std::endl;
				stbi_image_free(data);
			}
		}
		return skyTextureID;
	}
