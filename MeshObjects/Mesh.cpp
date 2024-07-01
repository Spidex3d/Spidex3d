#include "Mesh.h"
#include "../Shader/Shader.h"

Mesh* Mesh::Instance()
{
	static Mesh* Tmesh = new Mesh;

	return Tmesh;
	
}

bool Mesh::Initialize()
{
	//Shader defaultShader;
	//defaultShader.Load("../Shader/shaderFile/default.vert", "../Shader/shaderFile/default.frag");

	// put the buffer stuff in here
	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	//glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), position, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), position, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	//defaultShader.Use();
	Mesh::DrawTriangel();

	return true;
}

void Mesh::DrawTriangel()
{
	
	// GL Draw Triangel
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	
	glDrawArrays(GL_TRIANGLES, 0, 3);
	

}
