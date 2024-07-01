#include "pch.h"
#include "MainScreen.h"


int main(void)
{
    // Initialize the main window
    MainScreen::Instance()->Initialize();

    MainScreen::Instance()->SetImGui(); // ImGui setup

    // get the current opengl version number.
    std::cout << "GL_VERSION: " << glGetString(GL_VERSION) << std::endl;

    // Run The engine
    MainScreen::Instance()->Run();
    
    // close it all down and go to bed.
    // includes Imgui stuff
    MainScreen::Instance()->ShutDown();

    return 0;
}