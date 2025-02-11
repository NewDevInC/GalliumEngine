//
// Created by NewDevInC on 11.11.2024.
//

#ifndef SDL2_ENGINE_GLMESH_HPP
#define SDL2_ENGINE_GLMESH_HPP

#include <vector>
#include <GL/VAO.hpp>
#include <GL/EBO.hpp>
#include <GL/camera.hpp>
#include <GL/vertex.hpp>


class glMesh {
public:
    std::vector<vertex> vertices;
    std::vector<GLuint> indices;
    // std::vector <Texture> textures;

    glMesh(std::vector<vertex> &vertices, std::vector<GLuint> &indices, char *name);

    void drawMesh(glShader *&shader, glCamera *&camera);

private:
    char *name;
    VAO *pVAO = new VAO();

};


#endif //SDL2_ENGINE_GLMESH_HPP
