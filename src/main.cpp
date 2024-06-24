#include "MainScreen.h"
#include "pch.h"
//#include <glad\glad.h>
//#include <GLFW\glfw3.h>


bool IsRunning = true;
int main(void)
{

    MainScreen::Instance()->Initialize();

   /*
    GLFWwindow* window;

    // Initialize GLFW
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
    */

    // get the current opengl version number.
    std::cout << "GL_VERSION: " << glGetString(GL_VERSION) << std::endl;

    while (IsRunning)
    {
        MainScreen::Instance()->BgColour();

        MainScreen::Instance()->ClearScreen();

        MainScreen::Instance()->SplatBuffers();

        MainScreen::Instance()->PollEvents();

        
    }
    glfwTerminate();

    std::cout << "End Game" << std::endl;



    return 0;
}