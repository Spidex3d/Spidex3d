#include "Lights.h"

Lights* Lights::Instance()
{
    static Lights* light = new Lights;

    return light;
}

void Lights::LightSetUp()
{

}

void Lights::LightRender()
{
}
