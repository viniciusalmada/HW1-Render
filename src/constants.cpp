#include "constants.h"

namespace Const {
    // Constants
    const char* WINDOW_TITLE = "INF2610: Render (HW1)";

    // Files
    const char* VERTEX_PATH = "res/shaders/vertex.glsl";
    const char* FRAGMENT_STONES_PATH = "res/shaders/fragment-stones.glsl";
    const char* FRAGMENT_GOLF_PATH = "res/shaders/fragment-golfball.glsl";
    const char* STONES_MODEL = "res/obj/stones/stones.obj";
    const char* GOLF_MODEL = "res/obj/golfball/golfball.obj";

    // Shader fields
    const char* UNI_NORMAL_TEXTURE = "UNormalTexture";
    const char* UNI_DIFFUSE_TEXTURE = "UDiffuseTexture";
    const char* UNI_MATERIAL_AMBIENT = "UAmbientComp";
    const char* UNI_MATERIAL_DIFFUSE = "UDiffuseComp";
    const char* UNI_LIGHT_COLOR = "ULightColor";
    const char* UNI_LIGHT_POSITION = "ULightPos";
    const char* UNI_PROJ_MATRIX = "UProjMatrix";
    const char* UNI_MODEL_MATRIX = "UModelMatrix";
    const char* UNI_VIEW_MATRIX = "UViewMatrix";
    glm::vec3 AMBIENT_COMP_GOLF(0.2f, 0.2f, 0.2f);
    glm::vec3 AMBIENT_COMP_STONES(0.1f, 0.1f, 0.1f);
    glm::vec3 DIFFUSE_COMP_GOLF(0.8f, 0.8f, 0.8f);
}

namespace Color {
    const float WHITE[] = {1.0f, 1.0f, 1.0f, 1.0f};
}
