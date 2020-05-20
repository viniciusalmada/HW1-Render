#ifndef HW_TEXTURE_H
#define HW_TEXTURE_H

#include <GL/glew.h>
#include <assimp/types.h>

struct Texture {
    GLuint id;
    std::string type;
    aiString path;
};

#endif //HW_TEXTURE_H
