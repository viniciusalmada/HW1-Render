//
// Created by vinicius-devel on 5/19/20.
//

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <iostream>
#include <utility>
#include <SOIL/SOIL.h>
#include "model.h"

void Model::draw(Shader shader) {
    for (auto& mesh : this->meshes)
        mesh.draw(shader);
}

void Model::loadModel(const std::string& path) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_SortByPType |
                                                   aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR: ASSIMP\n" << importer.GetErrorString() << std::endl;
        return;
    }

    this->directory = path.substr(0, path.find_last_of('/'));

    this->processNode(scene->mRootNode, const_cast<aiScene*>(scene));
}

void Model::processNode(aiNode* node, aiScene* scene) {
    for (int i = 0; i < node->mNumMeshes; ++i) {
        aiMesh* aiM = scene->mMeshes[node->mMeshes[i]];
        this->meshes.push_back(this->processMesh(aiM, scene));
    }

    for (int i = 0; i < node->mNumChildren; ++i) {
        this->processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh* mesh, aiScene* scene) {
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    Texture textureNormal;
    Texture textureDiff;

    for (int i = 0; i < mesh->mNumVertices; ++i) {
        Vertex vertex{};
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;

        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.normal = vector;

        if (mesh->mTextureCoords[0]) {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.texCoords = vec;
        } else
            vertex.texCoords = glm::vec2{0.0f, 0.0f};

        vector.x = mesh->mTangents[i].x;
        vector.y = mesh->mTangents[i].y;
        vector.z = mesh->mTangents[i].z;
        vertex.tangent = vector;

        vector.x = mesh->mBitangents[i].x;
        vector.y = mesh->mBitangents[i].y;
        vector.z = mesh->mBitangents[i].z;
        vertex.bitangent = vector;

        vertices.push_back(vertex);
    }

    for (int j = 0; j < mesh->mNumFaces; ++j) {
        aiFace f = mesh->mFaces[j];
        for (int k = 0; k < f.mNumIndices; ++k) {
            indices.push_back(f.mIndices[k]);
        }
    }

    if (mesh->mMaterialIndex >= 0) {
        aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];

        textureNormal = loadMaterialTextures(mat, aiTextureType_HEIGHT, "texture_normal");

        textureDiff = loadMaterialTextures(mat, aiTextureType_DIFFUSE, "texture_diffuse");
    }

    return Mesh(vertices, indices, std::make_tuple(textureNormal, textureDiff));
}

Texture Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName) const {
    aiString str;
    mat->GetTexture(type, 0, &str);

    Texture texture;
    texture.id = TextureFromFile(str.C_Str(), this->directory);
    texture.type = std::move(typeName);
    texture.path = directory + '/' + str.C_Str();
    return texture;
}

GLuint Model::TextureFromFile(const char* path, const std::string& directory) {
    std::string file{path};
    file = directory + '/' + file;

    GLuint texID = 0;
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);

    int w, h;
    unsigned char* image = SOIL_load_image(file.c_str(), &w, &h, nullptr, SOIL_LOAD_RGB);
    if (image == nullptr) {
        printf("SOIL loading file \"%s\" error: %s \n", path, SOIL_last_result());
        return 0;
    }
    printf("SOIL loading file \"%s\" successful: %s \n", path, SOIL_last_result());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    SOIL_free_image_data(image);
    return texID;
}

glm::vec3 Model::center(float* maxZ) {
    float minX = 0.0f;
    float maxX = 0.0f;
    float minY = 0.0f;
    float maxY = 0.0f;
    float minZ = 0.0f;

    for (auto mesh : this->meshes) {
        mesh.extremes(minX, maxX, minY, maxY, minZ, *maxZ);
    }
    float centerX = minX + (maxX - minX) / 2.0f;
    float centerY = minY + (maxY - minY) / 2.0f;
    float centerZ = minZ + (*maxZ - minZ) / 2.0f;
    if (*maxZ == 0.0f) *maxZ = 0.50f;
    return glm::vec3(centerX, centerY, centerZ);
}

