//
// Created by NewDevInC on 11.11.2024.
//

#include "glMesh.hpp"

glMesh::glMesh(std::vector<vertex> &vertices, std::vector<GLuint> &indices, char *name) {
    this->name = name;

    this->vertices = vertices;
    this->indices = indices;

    this->pVAO->bind();

    VBO *pVBO = new VBO(this->vertices);
    EBO *pEBO = new EBO(this->indices);

    this->pVAO->linkAttrib(pVBO, 0, 3, GL_FLOAT, sizeof(vertex), nullptr); // Position
    this->pVAO->linkAttrib(pVBO, 1, 3, GL_FLOAT, sizeof(vertex), (void *) (3 * sizeof(float))); // Normals
    this->pVAO->linkAttrib(pVBO, 2, 3, GL_FLOAT, sizeof(vertex), (void *) (6 * sizeof(float))); // Base Colour
    this->pVAO->linkAttrib(pVBO, 3, 2, GL_FLOAT, sizeof(vertex), (void *) (9 * sizeof(float))); // UV

    this->pVAO->unbind();
    pVBO->unbind();
    pEBO->unbind();

}

void glMesh::drawMesh(glShader *&shader, glCamera *&camera) {

    shader->start();
    pVAO->bind();

    //TODO: For lighting:
    // glUniform3f(glGetUniformLocation(shader->id, "camPos"), camera->position.x, camera->position.y, camera->position.z);

    camera->exportMatrix(shader, "camMatrix");

    // Draw the actual mesh
    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, nullptr);

}
