//
// Created by NewDevInC on 2.10.2024.
//

#ifndef SDL2_ENGINE_EBO_HPP
#define SDL2_ENGINE_EBO_HPP

#include <GL/glew.h>
#include <vector>

class EBO {
public:
    explicit EBO(std::vector<GLuint> &indices, GLuint &id);

    explicit EBO(std::vector<GLuint> &indices);

    void bind(), unbind();

    ~EBO();

private:
    GLuint ID;
};


#endif //SDL2_ENGINE_EBO_HPP
