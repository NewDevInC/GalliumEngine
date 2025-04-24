//
// Created by NewDevInC on 19.4.2025.
//

#ifndef SDL2_ENGINE_TEXTURE_HPP
#define SDL2_ENGINE_TEXTURE_HPP

#include <GL/glShader.hpp>
#include <png.h>

class texture {

public:
    GLuint id;
    const char* type;
    GLuint unit;

    texture(const char* imageSrc, const char* type, GLuint slot);

    void assignUnit(glShader* &shader, const char* uniform, GLuint unit);

    void bind();
    void unbind();
    ~texture();

};

void readPng(const char* imageSrc, int &width, int &height, int &colourChannelType, png_bytep &imgData);

#endif //SDL2_ENGINE_TEXTURE_HPP
