#pragma once
#include "Shader.h"

class ShaderManager {
public:
    static void SetupShaders();
    static Shader* defaultGridShader; // Declare the shader as a static member
    static Shader* LightBulbShader; // Declare the shader as a static member
    static Shader* LightCubeShader; // Declare the shader as a static member
    static Shader* defaultShader; // Declare the shader as a static member
    static Shader* skyShader; // Declare the shader as a static member
};
