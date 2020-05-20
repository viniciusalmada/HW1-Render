#ifndef HW_MESH_H
#define HW_MESH_H

#include <vector>
#include <tuple>
#include "vertex.h"
#include "texture.h"
#include "shader.h"

class Mesh {

private:
    GLuint VAO;
    GLuint EBO;
    GLuint VBO[5];

    void setUpMesh();

public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::tuple<Texture, Texture> textures; // normal and diffuse

    Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices,
         std::tuple<Texture, Texture> textures);

    void draw(Shader shader);

    void extremes(float& minX, float& maxX,
                  float& minY, float& maxY,
                  float& minZ, float& maxZ) {

        minX = vertices.front().position.x;
        maxX = vertices.front().position.x;
        minY = vertices.front().position.y;
        maxY = vertices.front().position.y;
        minZ = vertices.front().position.z;
        maxZ = vertices.front().position.z;
        for (Vertex v : vertices) {
            minX = v.position.x < minX ? v.position.x : minX;
            maxX = v.position.x > maxX ? v.position.x : maxX;
            minY = v.position.y < minY ? v.position.y : minY;
            maxY = v.position.y > maxY ? v.position.y : maxY;
            minZ = v.position.z < minZ ? v.position.z : minZ;
            maxZ = v.position.z > maxZ ? v.position.z : maxZ;
        }
    }
};

#endif //HW_MESH_H
