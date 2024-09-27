#pragma once

#include "../Shader/Shader.h"


class App
{
public:
	static App* Instance();

    bool AppRun();

   

    void appInIt();

    void ShaderManager();

    Shader& getDefaultGridShader();

private:
    //Shader defaultShader;
    //Shader defaultGridShader;
    //Shader defaultTestShader;
    //Shader skyShader;
};

