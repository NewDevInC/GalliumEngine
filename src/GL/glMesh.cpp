//
// Created by NewDevInC on 11.11.2024.
//

#include "glMesh.hpp"

#include <utility>


glMesh::glMesh(std::vector<vertex> vertices, std::vector<GLuint> indices) {

    this->vertices = std::move(vertices);
    this->indices = std::move(indices);

    this->pVAO->bind();

    VBOinstance = new VBO(this->vertices);
    EBOinstance = new EBO(this->indices);

    this->pVAO->linkAttrib(VBOinstance, 0, 3, GL_FLOAT, sizeof(vertex), nullptr); // Position
    this->pVAO->linkAttrib(VBOinstance, 1, 3, GL_FLOAT, sizeof(vertex), (void *) offsetof(vertex, normal)); // Normals
    this->pVAO->linkAttrib(VBOinstance, 2, 2, GL_FLOAT, sizeof(vertex), (void *) offsetof(vertex, texUV)); // UV


    this->pVAO->unbind();
    VBOinstance->unbind();
    EBOinstance->unbind();

}

void glMesh::drawMesh(glCamera* &camera, const glm::mat4 &transformMatrix, glMaterial &material) {

    this->shader->start();
    pVAO->bind();

    glUniformMatrix4fv(glGetUniformLocation(this->shader->id, "worldMatrix"), 1, GL_FALSE, glm::value_ptr(transformMatrix));

    if(!material.hasTexture){
        glUniform1i(glGetUniformLocation(this->shader->id, "hasTexture"), GL_FALSE);

        glUniform3f(glGetUniformLocation(this->shader->id, "materialAmbient"), material.ambient.x, material.ambient.y, material.ambient.z);
        glUniform3f(glGetUniformLocation(this->shader->id, "materialDiffuse"), material.diffuse.x, material.diffuse.y, material.diffuse.z);
        glUniform3f(glGetUniformLocation(this->shader->id, "materialSpecular"), material.specular.x , material.specular.y, material.specular.z);

        glUniform1f(glGetUniformLocation(this->shader->id, "materialShine"), material.shine);

        glUniform3f(glGetUniformLocation(this->shader->id, "camPosition"), camera->position.x, camera->position.y, camera->position.z);
    }else {

    }



    camera->exportMatrix(shader.get(), "camMatrix");

    // Draw the actual mesh
    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, nullptr);


}

