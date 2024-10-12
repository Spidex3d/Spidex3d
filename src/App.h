#pragma once
#include <glm\glm.hpp>
#include "../Shader/ShaderManager.h"
//#include "Header\Configs.h"
//#include "Windows\WindowManager.h"

    
class App
{
public:
    App();
    ~App();

	static App* Instance();


    void AppRuning();

   
    void appInIt();
    void ImGuiInit();

private:
   
    
};

