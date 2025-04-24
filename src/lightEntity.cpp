//
// Created by NewDevInC on 23.4.2025.
//

#include "lightEntity.hpp"


lightEntity::lightEntity(GLfloat intensity, glm::vec3 colour) {

    this->intensity = intensity;
    this->colour = colour;
}

void lightEntity::draw(std::shared_ptr<glShader> &shader) {
    glUniform3f(glGetUniformLocation(shader->id, "lightColor"), this->colour.x, this->colour.y, this->colour.z);
    glUniform3f(glGetUniformLocation(shader->id, "lightPosition"), this->position.x, this->position.y, this->position.z);
}
