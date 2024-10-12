#include "App.h"
#include <iostream>
#include "../Grid/Grid.h"
#include "Header\MainScreen.h"




App::App()
{
}

App::~App()
{
}

App* App::Instance()
{
    static App* mainApp = new App;

    return mainApp;
}

void App::AppRuning()
{
   
   
}


void App::appInIt()
{
    
    std::cout << "App is running" << std::endl;

    
    // set up the grid
    Grid::Instance()->gridSetUp();
    ShaderManager::SetupShaders();
   
   
}

void App::ImGuiInit()
{
   // bool doc = true;
   // MainScreen::Instance()->MainDockSpace(&doc); // Docking
   //// MainScreen::Instance()->MainScean(windowManager.GetWindow());

}




