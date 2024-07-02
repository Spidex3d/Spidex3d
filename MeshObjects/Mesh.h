#pragma once
// Draw a mesh to display on screen

#include <glad\glad.h>

class Mesh
{
public:
	static Mesh* Instance();

	bool Initialize();

	void DrawTriangel();

private:
	/*
	float position[6] = {
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.0f,  0.5f
	};
	*/
	/*
	float vertices[18] = {
		// positions         // colors
		 -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		  0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		  0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 

	};
	*/
	/*
	float position[6] = {
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.5f,  0.5f
	};
	*/
	
	/*
	float vertices[12] = {
		// first triangle
		-0.5f,  -0.5f,   // top right
		 0.5f,  -0.5f,   // bottom right
	     0.5f,   0.5f,   // top left 
	   // second tria
		 0.5f,   0.5f,   // bottom right
	    -0.5f,   0.5f,   // bottom left
	    -0.5f,  -0.5f   // top left
		}; 
		*/

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
	


};

