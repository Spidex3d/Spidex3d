#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <vector>

GLuint GridVAO, GridVBO;


// Function to create the grid vertices
std::vector<float> createGridVertices(float size, int divisions) {
    

    std::vector<float> vertices;
    float step = size / divisions;
    float halfSize = size / 2.0f;

    for (int i = 0; i <= divisions; ++i) {
        float coord = -halfSize + i * step;
        // Vertical lines
        vertices.push_back(coord);
        vertices.push_back(0.0f);
        vertices.push_back(-halfSize);
        vertices.push_back(coord);
        vertices.push_back(0.0f);
        vertices.push_back(halfSize);
        // Horizontal lines
        vertices.push_back(-halfSize);
        vertices.push_back(0.0f);
        vertices.push_back(coord);
        vertices.push_back(halfSize);
        vertices.push_back(0.0f);
        vertices.push_back(coord);
    }
    return vertices;
}
/*
// ################################################## grid ########################
const auto FILL = fill; // 20 x 20 Grid do something with this at runtime
float SIZE = 1.0f;
class test {
public:
    void gridSetUp() {
        //std::vector<float> gridVertices = createGridVertices(1.0f, 20);
        std::vector<float> gridVertices = createGridVertices(SIZE, FILL);

        glGenVertexArrays(1, &GridVAO);
        glGenBuffers(1, &GridVBO);

        glBindVertexArray(GridVAO);
        glBindBuffer(GL_ARRAY_BUFFER, GridVBO);
        glBufferData(GL_ARRAY_BUFFER, gridVertices.size() * sizeof(float), gridVertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }
};
// ################################################## grid End ########################

*/