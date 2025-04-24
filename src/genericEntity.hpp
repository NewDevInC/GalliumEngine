//
// Created by NewDevInC on 23.4.2025.
//

#ifndef SDL2_ENGINE_GENERICENTITY_HPP
#define SDL2_ENGINE_GENERICENTITY_HPP

#include <glm/glm.hpp>
#include <GL/glShader.hpp>
#include <GL/camera.hpp>
#include <memory>

enum class entityType { Game, Light};

class genericEntity {
public:

    GLuint shaderId = 0;

    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);

    virtual void draw(std::shared_ptr<glShader> &shader) {};
    virtual void draw(std::shared_ptr<glShader> &shader, glCamera* &camera) {};

    [[nodiscard]] virtual entityType getType() const = 0;

    virtual ~genericEntity() = default;
};


#endif //SDL2_ENGINE_GENERICENTITY_HPP
