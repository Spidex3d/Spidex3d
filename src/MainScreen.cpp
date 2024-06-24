#include "MainScreen.h"
#include "pch.h";

MainScreen* MainScreen::Instance()
{
	static MainScreen* screen = new MainScreen;

	return screen;
}

bool MainScreen::Initialize()
{

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);  // So this is 4.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);  // and this .6  = 4.6
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 600, "Spidex 3d Engine", NULL, NULL);

    if (!window)
    {
        // give an error message
        std::cout << "Failed to Create a window" << std::endl;
        glfwTerminate();
        return -1;

    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        // give an error message
        std::cout << "Failed to Load Glad" << std::endl;
        return -1;
    }

	return true;
}

void MainScreen::ClearScreen()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void MainScreen::SplatBuffers()
{
    glfwSwapBuffers(window);
}

void MainScreen::PollEvents()
{
    glfwPollEvents();
}

void MainScreen::ShutDown()
{

}

void MainScreen::BgColour()
{
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

}
