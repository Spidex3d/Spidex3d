#include "ShaderManager.h"
#include <iostream>

// Define the static member
Shader * ShaderManager::defaultGridShader = nullptr; // the grid shader
Shader * ShaderManager::LightBulbShader = nullptr;   // the light bulb shader
Shader * ShaderManager::LightCubeShader = nullptr;   // the obj shaders 
Shader * ShaderManager::defaultShader = nullptr;   // the obj shaders 
Shader * ShaderManager::skyShader = nullptr;   // the sky shaders 

void ShaderManager::SetupShaders() {
    // Initialize the shader
    defaultGridShader = new Shader("Shader/shaderFile/default_Grid.vert", "Shader/shaderFile/default_Grid.frag");
  
    LightBulbShader = new Shader("Shader/shaderFile/bulb.vert", "Shader/shaderFile/bulb.frag");
  
    LightCubeShader = new Shader("Shader/shaderFile/light.vert", "Shader/shaderFile/light.frag");

    defaultShader = new Shader("Shader/shaderFile/default.vert", "Shader/shaderFile/default.frag");

    skyShader = new Shader("Shader/shaderFile/sky.vert", "Shader/shaderFile/sky.frag");
}
