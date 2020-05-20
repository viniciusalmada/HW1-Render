#ifndef HW_CONSTANTS_H
#define HW_CONSTANTS_H

#include <string>
#include <glm/vec3.hpp>

namespace Const {
    // Constants
    extern const char* WINDOW_TITLE;

    // Files
    extern const char* VERTEX_PATH;
    extern const char* FRAGMENT_STONES_PATH;
    extern const char* FRAGMENT_GOLF_PATH;
    extern const char* STONES_MODEL;
    extern const char* GOLF_MODEL;

    // Shader fields
    extern const char* UNI_NORMAL_TEXTURE;
    extern const char* UNI_DIFFUSE_TEXTURE;
    extern const char* UNI_MATERIAL_AMBIENT;
    extern const char* UNI_MATERIAL_DIFFUSE;
    extern const char* UNI_LIGHT_COLOR;
    extern const char* UNI_LIGHT_POSITION;
    extern const char* UNI_PROJ_MATRIX ;
    extern const char* UNI_MODEL_MATRIX;
    extern const char* UNI_VIEW_MATRIX ;
    extern glm::vec3 AMBIENT_COMP_GOLF;
    extern glm::vec3 AMBIENT_COMP_STONES;
    extern glm::vec3 DIFFUSE_COMP_GOLF;
}

namespace Color {
    extern const float WHITE[];
}
#endif //HW_CONSTANTS_H
