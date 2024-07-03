#pragma once
// Draw a mesh to display on screen

#include <glad\glad.h>
#include <stb\stb_image.h>


class Mesh
{
public:
	static Mesh* Instance();

	bool Initialize();

	void DrawTriangel();

//private:
	float vertices[32] =
	{
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices[6] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
	
	/*
	float vertices[36] = {
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),(void*)0);
		// first triangle      Colour
		-0.5f,  -0.5f,  0.0f, 1.0f, 0.0f, 0.0f,
		 0.5f,  -0.5f,  0.0f, 0.0f, 1.0f, 0.0f,
		 0.5f,   0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 
		 // second triangle    Colour
		 0.5f,   0.5f,  0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f,   0.5f,  0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f,  -0.5f,  0.0f, 1.0f, 0.0f, 0.0f 
	};
	
		*/
	

};

