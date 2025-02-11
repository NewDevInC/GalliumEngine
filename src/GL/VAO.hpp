//
// Created by NewDevInC on 2.10.2024.
//

#ifndef SDL2_ENGINE_VAO_HPP
#define SDL2_ENGINE_VAO_HPP

#include <GL/glew.h>
#include <GL/VBO.hpp>

class VAO {
public:
    explicit VAO(GLuint &id);

    explicit VAO();

    void linkAttrib(VBO *&VBO, GLuint layout, GLuint components, GLenum type, GLsizeiptr stride, void *offset);

    void bind(), unbind();

    ~VAO();

private:
    GLuint id;
};


#endif //SDL2_ENGINE_VAO_HPP
