#pragma once
#include "../Shader/ShaderManager.h"



class App
{
public:
    App();
    ~App();

	static App* Instance();

    bool AppRun();

   

    void appInIt();



   

private:
    
    bool IsRunning = true;
};

