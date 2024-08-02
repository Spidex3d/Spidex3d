#pragma once
// Draw a mesh to display on screen

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb\stb_image.h>
#include "../Shader/Shader.h"

#include "../src/Header/Configs.h"

#include "../MeshObjects/Vertices.h"

#include <iostream>


GLuint VBO;
GLuint VAO;
GLuint planeVBO;
GLuint planeVAO;

GLuint bufferId;
const char* label = "My Cube";

void Mesh_Setup()
{

    //##################### our default Cube ####################
    
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
   
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    //location = 0 attribute 3 vertices        strid 8				start at 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Texture location 1
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // colour location = 2
    //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    //glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glDeleteBuffers(1, &VBO);

    glObjectLabel(GL_BUFFER, bufferId, -1, label);
   
}

void FloorMesh() { // draw a floor mesh
    glGenVertexArrays(1, &planeVBO);
    glBindVertexArray(planeVBO);
    
    glGenBuffers(1, &planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);

    //location = 0 attribute 3 vertices        strid 5				start at 0
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    // Texture location 1
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glDeleteBuffers(1, &VBO);

    glObjectLabel(GL_BUFFER, bufferId, -1, label); // might be abel to use this to give it a name
    
}


void Mesh_CleanUp()
{
   glDeleteVertexArrays(1, &VAO);

}