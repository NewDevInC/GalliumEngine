//
// Created by NewDevInC on 11.11.2024.
//

#ifndef SDL2_ENGINE_GLMESH_HPP
#define SDL2_ENGINE_GLMESH_HPP

#include <vector>
#include <utility>

#include <GL/VAO.hpp>
#include <GL/EBO.hpp>
#include <GL/camera.hpp>
#include <GL/vertex.hpp>
#include <GL/glMaterial.hpp>
#include <memory>


class glMesh {
public:
    std::vector<vertex> vertices;
    std::vector<GLuint> indices;

    std::shared_ptr<glShader> shader;

    glMesh(std::vector<vertex> vertices, std::vector<GLuint> indices);

    void drawMesh(glCamera* &camera, const glm::mat4 &transformMatrix, glMaterial &material);


private:
    VAO *pVAO = new VAO();
    VBO *VBOinstance = nullptr;
    EBO *EBOinstance = nullptr;
};


#endif //SDL2_ENGINE_GLMESH_HPP
