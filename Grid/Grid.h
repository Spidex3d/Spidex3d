#pragma once
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

/**/