//
// Created by NewDevInC on 2.10.2024.
//

#include "VBO.hpp"

VBO::VBO(std::vector<vertex> &vertices, GLint &id) {
    this->id = id;
    glGenBuffers(1, &this->id);
    glBindBuffer(GL_ARRAY_BUFFER, this->id);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex), vertices.data(), GL_STATIC_DRAW);
}

VBO::VBO(std::vector<vertex> &vertices) {
    glGenBuffers(1, &this->id);
    glBindBuffer(GL_ARRAY_BUFFER, this->id);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex), vertices.data(), GL_STATIC_DRAW);
}


void VBO::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, this->id);
}

void VBO::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VBO::~VBO() {
    glDeleteBuffers(1, &this->id);
}

