#include "mesh.h"
#include "constants.h"

void Mesh::setUpMesh() {
    /* Generates the Vertex Array Object,
     * the Element Buffer Object and the
     * buffers of the Vertex attributes */
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(5, this->VBO);
    glGenBuffers(1, &this->EBO);

    // Bind to VAO
    glBindVertexArray(this->VAO);

    // Buffer vertex position at 0 (3 per vertex)
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, position));

    // Buffer vertex normal at 1 (3 per vertex)
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, normal));

    // Buffer vertex texture coordinates at 2 (2 per vertex)
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, texCoords));

    // Buffer vertex tangent at 3 (3 per vertex)
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO[3]);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, tangent));

    // Buffer vertex tangent at 4 (3 per vertex)
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO[4]);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, bitangent));

    // Bind and buffer element object
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);
    glBindVertexArray(0);
}

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::tuple<Texture, Texture> textures)
        : vertices(vertices), indices(indices), textures(textures) {
    this->setUpMesh();
}

void Mesh::draw(Shader shader) {
    // Get normal texture uniform location
    GLint tn = glGetUniformLocation(shader.mProgram, Const::UNI_NORMAL_TEXTURE);
    glUniform1i(tn, 0);
    // Active 0 texture slot and bind
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, std::get<0>(this->textures).id);

    if (std::get<1>(this->textures).id != 0) {
        GLint td = glGetUniformLocation(shader.mProgram, Const::UNI_DIFFUSE_TEXTURE);
        glUniform1i(td, 1); // pass texture slot location
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, std::get<1>(this->textures).id);
    }

    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}
