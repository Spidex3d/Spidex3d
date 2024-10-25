#include "Lights.h"
#include "../Shader/ShaderManager.h"
#include "../Objects/spxObjLoader.h"

//extern spxObjLoader lightMesh;

Lights* Lights::Instance()
{
    static Lights* light = new Lights;

    return light;
}

 void Lights::ImGuiLightsSetUp()
{
     
    
}

void Lights::LightSetUp()
{
    
   

}

void Lights::LightRender()
{
}
