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

	// put the buffer stuff in here
	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//location = 0 attribute 3 vertices        strid 6
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// colour location = 1
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 *sizeof(float)));
	glEnableVertexAttribArray(1);

	defaultShader.Use();
	Mesh::DrawTriangel();
	defaultShader.Destroy();

	return true;
}

void Mesh::DrawTriangel()
{
	
	// GL Draw Triangel
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	
	glDrawArrays(GL_TRIANGLES, 0, 3);
	

}
