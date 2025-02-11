//
// Created by NewDevInC on 2.10.2024.
//

#ifndef SDL2_ENGINE_VBO_HPP
#define SDL2_ENGINE_VBO_HPP

#include <GL/glew.h>
#include <GL/vertex.hpp>
#include <vector>

class VBO {
public:
    explicit VBO(std::vector<vertex> &vertices, GLint &id);

    explicit VBO(std::vector<vertex> &vertices);

    void bind(), unbind();

    ~VBO();

private:
    GLuint id;

};


#endif //SDL2_ENGINE_VBO_HPP
