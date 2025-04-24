//
// Created by NewDevInC on 23.4.2025.
//

#ifndef SDL2_ENGINE_LIGHTENTITY_HPP
#define SDL2_ENGINE_LIGHTENTITY_HPP

#include <GL/glew.h>
#include <genericEntity.hpp>

class lightEntity : public genericEntity {
public:
    explicit lightEntity(GLfloat intensity = 1.0f, glm::vec3 colour = glm::vec3(1.0f, 1.0f, 1.0f));

    GLfloat intensity;
    glm::vec3 colour;
    // glm::vec3 color = colour; if you are american, and like writing colour incorrectly.

    void draw(std::shared_ptr<glShader> &shader) override;

    [[nodiscard]] entityType getType() const override{ return entityType::Light; };

};


#endif //SDL2_ENGINE_LIGHTENTITY_HPP
