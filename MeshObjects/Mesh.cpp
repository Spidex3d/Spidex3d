//#define STB_IMAGE_IMPLEMENTATION
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "Mesh.h"
#include "Vertices.h"
//#include "../Shader/Shader.h"
#include "../src/Textures.h"


	Mesh* Mesh::Instance()
	{
		static Mesh* Tmesh = new Mesh;

		return Tmesh;

	}

	bool Mesh::Initialize()
	{
		//Shader defaultShader;
		defaultShader.Load("Shader/shaderFile/default.vert", "Shader/shaderFile/default.frag");

		//##################### Texture Test ####################
		//unsigned int VBO, VAO, EBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(planeIndices), planeIndices, GL_STATIC_DRAW);

		//location = 0 attribute 3 vertices        strid 8				start at 0
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// colour location = 1
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		// Texture location 2
		//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		//glEnableVertexAttribArray(2);

		// flip image
		stbi_set_flip_vertically_on_load(true);

		int width, height, nrChannels;

		std::string texPath = "Textures/";
		std::string texImg = "github.jpg";

		defaultMap = loadTexture((texPath + texImg).c_str());

		//#########################################

		defaultShader.Use();

		

		//glBindVertexArray(VAO);

		Mesh::DrawTriangel();


		Mesh::CleanUp();

		return true;
	}

	void Mesh::DrawTriangel()
	{
		
		float time = glfwGetTime();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, defaultMap);

		defaultShader.Use();

		glm::mat4 projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		defaultShader.SendUniformData("projection", projection);

		glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		defaultShader.SendUniformData("view", view);
	
		

		glBindVertexArray(VAO);
		for (unsigned int i = 0; i < 10; i++)
		{
			// create transformations
			glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			//model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
			model = glm::rotate(model, glm::radians(angle) * time, glm::vec3(1.0f, 0.3f, 0.5f));
			defaultShader.SendUniformData("model", model);
			


			glDrawArrays(GL_TRIANGLES, 0, 36);
			//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}

	}

	void Mesh::CleanUp()
	{
		defaultShader.Destroy();
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}
