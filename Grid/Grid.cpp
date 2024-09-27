#include "grid.h"

//void gridSetUp() {
//    std::vector<float> gridVertices = createGridVertices(1.0f, 20);
//    //std::vector<float> gridVertices = createGridVertices(SIZE, FILL);
//
//    glGenVertexArrays(1, &GridVAO);
//    glGenBuffers(1, &GridVBO);
//
//    glBindVertexArray(GridVAO);
//    glBindBuffer(GL_ARRAY_BUFFER, GridVBO);
//    glBufferData(GL_ARRAY_BUFFER, gridVertices.size() * sizeof(float), gridVertices.data(), GL_STATIC_DRAW);
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//}

Grid* Grid::Instance()
{
    static Grid* mainGrid = new Grid;

    return mainGrid;
}

std::vector<float> Grid::createGridVertices(float size, int divisions)
{
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

void Grid::gridSetUp()
{
    //std::vector<float> gridVertices = createGridVertices(1.0f, 20);
    gridVertices = createGridVertices(1.0f, 20);

    glGenVertexArrays(1, &GridVAO);
    glGenBuffers(1, &GridVBO);

    glBindVertexArray(GridVAO);
    glBindBuffer(GL_ARRAY_BUFFER, GridVBO);
    glBufferData(GL_ARRAY_BUFFER, gridVertices.size() * sizeof(float), gridVertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

}

void Grid::setUpRender()
{
    //app->getDefaultGridShader().Use();
   
    //app->getDefaultGridShader().SendUniformData("projection", projection);
    //
    //app->getDefaultGridShader().SendUniformData("view", view);
    //
    //model = glm::mat4(1.0f);
    //
    //model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f)); // this is better
    //model = glm::scale(model, glm::vec3(20.0f, 0.0f, 20.0f));
    //app->getDefaultGridShader().SendUniformData("model", model);

}

void Grid::gridRender()
{
    glBindVertexArray(GridVAO);
    glDrawArrays(GL_LINES, 0, gridVertices.size() / 3);
    glBindVertexArray(0);
}
