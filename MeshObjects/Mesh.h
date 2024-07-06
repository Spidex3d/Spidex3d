#pragma once
// Draw a mesh to display on screen

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <stb\stb_image.h>
#include "../Shader/Shader.h"
#include "../src/Input.h"

#include "../src/Common.h"



    class Mesh
    {
    public:
        static Mesh* Instance();

        bool Initialize();

        void DrawTriangel();

        void CleanUp();

    private:
        Shader defaultShader;

        unsigned int defaultMap;

        unsigned int VBO, VAO, EBO;

        glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
        glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

        float deltaTime = 0.0f;
        float lastFrame = 0.0f;
        float fov = 45.0f;
        /*
        float vertices[32] =
        {
            // positions          // colors           // texture coords
             0.5f,  0.8f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
             0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
            -0.5f,  0.8f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // top left
        };
        unsigned int indices[6] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };
        */



    };

