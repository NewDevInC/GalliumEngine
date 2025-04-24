//
// Created by NewDevInC on 21.4.2025.
//

#include "gameEntity.hpp"

gameEntity::gameEntity() = default;

void gameEntity::addMesh(glMesh &mesh) {
    this->meshes.push_back(mesh);
}

void gameEntity::addMaterial(glMaterial &material) {
    this->materials.push_back(material);
}

void gameEntity::correlateMeshMaterial(std::vector<const char*> &requestedMaterials) {

    for(size_t i = 0; i < requestedMaterials.size(); i++){
        for(auto &material : materials){
            if(!strcmp(material.getName(), requestedMaterials[i])){
                this->usedMaterial[i] = &material;
            }
        }
    }

    std::destroy(requestedMaterials.begin(), requestedMaterials.end());

}

glm::mat4 gameEntity::worldMatrix() const {
    auto transformation = glm::mat4(1.0f);

    transformation = glm::translate(transformation, this->position);
    transformation = glm::rotate(transformation, glm::radians(this->rotation.x), glm::vec3(1,0,0));
    transformation = glm::rotate(transformation, glm::radians(this->rotation.y), glm::vec3(0,1,0));
    transformation = glm::rotate(transformation, glm::radians(this->rotation.z), glm::vec3(0,0,1));

    transformation = glm::scale(transformation, this->scale);

    return transformation;

}


void gameEntity::draw(std::shared_ptr<glShader> &shader, glCamera* &camera) {
    for(size_t i = 0; i < meshes.size(); i++){
        meshes[i].shader = shader;
        meshes[i].drawMesh(camera, worldMatrix(), *usedMaterial[i % usedMaterial.size()]);
    }

}

