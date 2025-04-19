//
// Created by NewDevInC on 11.11.2024.
//

#include "glMesh.hpp"

glMesh::glMesh(std::vector<vertex> &vertices, std::vector<GLuint> &indices, const char *name) {
    this->name = name;

    this->vertices = vertices;
    this->indices = indices;

    this->pVAO->bind();

    VBO *pVBO = new VBO(this->vertices);
    EBO *pEBO = new EBO(this->indices);

    this->pVAO->linkAttrib(pVBO, 0, 3, GL_FLOAT, sizeof(vertex), nullptr); // Position
    this->pVAO->linkAttrib(pVBO, 1, 3, GL_FLOAT, sizeof(vertex), (void *) offsetof(vertex, normal)); // Normals
    this->pVAO->linkAttrib(pVBO, 2, 2, GL_FLOAT, sizeof(vertex), (void *) offsetof(vertex, texUV)); // UV


    this->pVAO->unbind();
    pVBO->unbind();
    pEBO->unbind();

}

glMesh::glMesh(glShader* &shader,std::vector<vertex> &vertices, std::vector<GLuint> &indices, const char *name) {
    this->name = name;

    this->shader = shader;
    this->vertices = vertices;
    this->indices = indices;

    this->pVAO->bind();

    VBO *pVBO = new VBO(this->vertices);
    EBO *pEBO = new EBO(this->indices);

    this->pVAO->linkAttrib(pVBO, 0, 3, GL_FLOAT, sizeof(vertex), nullptr); // Position
    this->pVAO->linkAttrib(pVBO, 1, 3, GL_FLOAT, sizeof(vertex), (void *) offsetof(vertex, normal)); // Normals
    this->pVAO->linkAttrib(pVBO, 2, 2, GL_FLOAT, sizeof(vertex), (void *) offsetof(vertex, texUV)); // UV


    this->pVAO->unbind();
    pVBO->unbind();
    pEBO->unbind();

}

void glMesh::drawMesh(glCamera *&camera) {

    this->shader->start();
    pVAO->bind();

    glUniform3f(glGetUniformLocation(this->shader->id, "camPosition"), camera->position.x, camera->position.y, camera->position.z);
    camera->exportMatrix(shader, "camMatrix");

    // Draw the actual mesh
    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, nullptr);


}
