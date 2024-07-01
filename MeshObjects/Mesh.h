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
	
	float position[6] = {
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.0f,  0.5f
	};
	
	/*
	float position[6] = {
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.5f,  0.5f
	};
	*/
	
	/*
	float position[12] = {
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


};

