//
// Created by NewDevInC on 21.4.2025.
//

#ifndef SDL2_ENGINE_GLMATERIAL_HPP
#define SDL2_ENGINE_GLMATERIAL_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GL/texture.hpp>

#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>

#include <util.hpp>

class glMaterial {
public:
    glMaterial() = default;
    explicit glMaterial(const char* name);

    glm::vec3 ambient = glm::vec3(1.0f);
    glm::vec3 diffuse = glm::vec3(0.8f);
    glm::vec3 specular = glm::vec3(0.5f);
    glm::vec3 emission = glm::vec3(0.0f);

    GLfloat shine = 1.0f;
    GLfloat transparency = 1.0f;

    bool hasTexture = false;

    std::vector<texture> textures;
    std::vector<const char*> textureTypes;

    const char* getName() { return this->name; };

private:
    const char* name = "null";

};


#endif //SDL2_ENGINE_GLMATERIAL_HPP
