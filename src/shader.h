#ifndef HW_SHADER_H
#define HW_SHADER_H

#include <GL/glew.h>

class Shader {

public:
    GLuint mProgram;

    Shader(const char *vertexPath, const char *fragPath);

    void use() const { glUseProgram(this->mProgram); }

};


#endif //HW_SHADER_H
