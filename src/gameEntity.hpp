//
// Created by NewDevInC on 21.4.2025.
//

#ifndef SDL2_ENGINE_GAMEENTITY_HPP
#define SDL2_ENGINE_GAMEENTITY_HPP

#include <genericEntity.hpp>
#include <GL/glMesh.hpp>
#include <GL/glMaterial.hpp>
#include <map>


class gameEntity : public genericEntity {
public:


    gameEntity();

    void addMesh(glMesh &mesh);
    void addMaterial(glMaterial &material);

    void correlateMeshMaterial(std::vector<const char*> &requestedMaterials);

    void draw(std::shared_ptr<glShader> &shader, glCamera* &camera) override;

    [[nodiscard]] entityType getType() const override{ return entityType::Game; };

private:

    [[nodiscard]] glm::mat4 worldMatrix() const;

    std::vector<glMesh> meshes = {};
    std::vector<glMaterial> materials = {};
    std::map<GLuint, glMaterial*> usedMaterial = {};

    // Uses meshes.size() as key, since we are drawing the meshes one after another.


};


#endif //SDL2_ENGINE_GAMEENTITY_HPP
