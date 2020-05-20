#ifndef HW_OBJECT_H
#define HW_OBJECT_

#include <glm/ext.hpp>
#include "shader.h"
#include "constants.h"

class Object {
private:
    glm::vec3* ambientColor;
    glm::vec3* diffuseColor;

public:
    Object(const char* modelPath, const char* fragmentPath, glm::vec3* ambientColor, glm::vec3* diffuseColor)
            : modelPath(modelPath), fragmentPath(fragmentPath), ambientColor(ambientColor),
              diffuseColor(diffuseColor) {}

    const char* fragmentPath;
    const char* modelPath;

    void setLights(Shader shader) {
        GLint ambientLoc = glGetUniformLocation(shader.mProgram, Const::UNI_MATERIAL_AMBIENT);
        glUniform3fv(ambientLoc, 1, glm::value_ptr(*ambientColor));
        if (diffuseColor != nullptr) {
            GLint diffuseLoc = glGetUniformLocation(shader.mProgram, Const::UNI_MATERIAL_DIFFUSE);
            glUniform3fv(diffuseLoc, 1, glm::value_ptr(*diffuseColor));
        }
    };
};


#endif //HW_OBJECT_H
