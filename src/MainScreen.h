#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>

class MainScreen
{

public:

	static MainScreen* Instance();

	bool Initialize();
	void ClearScreen();
	void SplatBuffers();
	void PollEvents();
	void ShutDown();

	void BgColour();


private:
	GLFWwindow* window;


};

