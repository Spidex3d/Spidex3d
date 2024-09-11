#pragma once
#include <glad\glad.h>
#include <GLFW/glfw3.h>

class defaultCube
{
public:
    static defaultCube* Instance();

    void MaindefaultCube();
    void draw();

private:
    int idxCube = 0;
    GLuint VBO, VAO;
    void setupCube();
};

