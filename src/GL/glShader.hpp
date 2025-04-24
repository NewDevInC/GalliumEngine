//
// Created by NewDevInC on 2.10.2024.
//

#ifndef SDL2_ENGINE_GLSHADER_HPP
#define SDL2_ENGINE_GLSHADER_HPP

#include <GL/glew.h>
#include <util.hpp>

class glShader {

public:
    GLuint id;

    glShader(const char *vertexGLSL, const char *fragmentGLSL);

    ~glShader();

    void start();

private:

};


#endif //SDL2_ENGINE_GLSHADER_HPP
