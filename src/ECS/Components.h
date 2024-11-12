#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <string>

struct Transform {
    glm::vec3 position;
    glm::vec3 scale;

    Transform() : position(0.0f, 0.0f, 0.0f), scale(1.0f, 1.0f, 1.0f) {}
};

struct Cube {
    std::string name;
    Transform transform;

    Cube() : name("DefaultCube") {}
};

/*
// This is the components of each object
struct Transform {
    glm::mat4 objPosition;

    Transform() {
        objPosition = glm::mat4(1.0f); // Initialize to identity matrix
        objPosition = glm::translate(objPosition, glm::vec3(1.0f, 0.0f, 2.0f)); // Apply translation
    }
    glm::vec3 getTranslation() const {
        return glm::vec3(objPosition[3]); // Extract the translation vector
    }
    

};

struct Scaleobj {
    glm::mat4 objScale;

    Scaleobj() {
        objScale = glm::mat4(1.0f);
        objScale = glm::scale(objScale, glm::vec3(1.0f, 0.0f, 2.0f));
    }
    glm::vec3 getObjScale () const {
        return glm::vec3(objScale[3]); // Extract the translation vector
    }
};
*/