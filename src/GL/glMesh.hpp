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

    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 worldMatrix = glm::mat4(1.0f);

    glShader* shader;

    glMesh(glShader* &shader, std::vector<vertex> &vertices, std::vector<GLuint> &indices, const char *name);
    glMesh(std::vector<vertex> &vertices, std::vector<GLuint> &indices, const char *name);

    void drawMesh(glCamera *&camera);

private:
    const char *name;
    VAO *pVAO = new VAO();

};


#endif //SDL2_ENGINE_GLMESH_HPP
