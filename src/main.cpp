#include "MainScreen.h"
#include "pch.h"


bool IsRunning = true;
int main(void)
{

    MainScreen::Instance()->Initialize();

 
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