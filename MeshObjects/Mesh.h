#pragma once
// Draw a mesh to display on screen

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb\stb_image.h>
#include "../Shader/Shader.h"

#include "../src/Common.h"

#include "../MeshObjects/Vertices.h"

// unsigned int VBO, VAO, EBO, FBO;
GLuint VBO, VAO, EBO, FBO, RBO;
GLuint txt_id;

void Mesh_Setup()
{

    //##################### Texture Test ####################
    //unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
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

    glBindVertexArray(0);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Create_FrameBuffer()
{
    glGenFramebuffers(1, &FBO);

}



void Mesh_CleanUp()
{
    glDeleteVertexArrays(1, &VAO);
   

}