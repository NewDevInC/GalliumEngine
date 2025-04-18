//
// Created by NewDevInC on 11.11.2024.
//

#ifndef SDL2_ENGINE_VERTEX_HPP
#define SDL2_ENGINE_VERTEX_HPP

#include <glm/glm.hpp>

struct vertex {
    glm::vec3 position;
    glm::vec2 texUV;
    glm::vec3 normal;
};

#endif //SDL2_ENGINE_VERTEX_HPP
