//
// Created by NewDevInC on 2.10.2024.
//

#include "VAO.hpp"


VAO::VAO(GLuint &id) {
    this->id = id;
    glGenVertexArrays(1, &this->id);
}

VAO::VAO() {
    glGenVertexArrays(1, &this->id);
}

void VAO::linkAttrib(VBO* &VBO, GLuint layout, GLuint components, GLenum type, GLsizeiptr stride, void *offset) {
    VBO->bind();
    glVertexAttribPointer(layout, components, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    VBO->unbind();
}

void VAO::bind() {
    glBindVertexArray(this->id);
}

void VAO::unbind() {
    glBindVertexArray(0);
}


VAO::~VAO() {
    glDeleteVertexArrays(1, &this->id);
}