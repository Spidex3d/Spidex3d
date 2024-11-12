#pragma once

#include "../ECS/Components.h"
#include "../Shader/Shader.h"

Shader defaultShader;



void renderCube(const Transform& transform) {

    defaultShader.Load("Shader/shaderFile/default.vert", "Shader/shaderFile/default.frag");
    // Apply transformations

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, transform.position);
    model = glm::scale(model, transform.scale);

    defaultShader.SendUniformData("model", model);

    // Set the model matrix in your shader
    // glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

     // Render the cube (assuming you have a VAO and VBO set up for a cube)
     //glBindVertexArray(cubeVAO);
     //glDrawArrays(GL_TRIANGLES, 0, 36);
     //glBindVertexArray(0);
}
