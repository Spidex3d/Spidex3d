#include "App.h"
#include <iostream>
//#include "../SkyBox/skyBox.h"
#include "../Grid/Grid.h"




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

bool App::AppRun()
{
    

    return true;
}


void App::appInIt()
{
    float angel = 0.0f;  // to do with the light
    std::cout << "App is running" << std::endl;

    
    // set up the grid
    Grid::Instance()->gridSetUp();
    ShaderManager::SetupShaders();
   
}




