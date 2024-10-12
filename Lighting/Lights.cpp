#include "Lights.h"
#include "../Shader/ShaderManager.h"

Lights* Lights::Instance()
{
    static Lights* light = new Lights;

    return light;
}

void Lights::LightSetUp()
{
    //ShaderManager::LightCubeShader->Use();
    //ShaderManager::LightCubeShader->setMat4("view", view);

}

void Lights::LightRender()
{
}
