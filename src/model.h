#ifndef HW_MODEL_H
#define HW_MODEL_H

#include <string>
#include "mesh.h"
#include <assimp/scene.h>

class Model {

public:
    explicit Model(const char *path) { this->loadModel(path); }

    void draw(Shader shader);

    std::vector<Mesh> meshes;
    std::string directory;

    glm::vec3 center(float* pDouble);

private:
    void loadModel(const std::string &path);

    void processNode(aiNode *node, aiScene *scene);

    Mesh processMesh(aiMesh *mesh, aiScene *scene);

    Texture loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName) const;

    static GLuint TextureFromFile(const char* path, const std::string& directory);
};

#endif //HW_MODEL_H
