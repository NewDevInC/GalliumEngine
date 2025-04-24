//
// Created by NewDevInC on 11.12.2024.
//

#ifndef SDL2_ENGINE_OBJ_HPP
#define SDL2_ENGINE_OBJ_HPP


#include <GL/glew.h>
#include <GL/vertex.hpp>
#include <gameEntity.hpp>

#include <vector>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>

#include <util.hpp>


std::unique_ptr<gameEntity> importObj(const char *file);
std::vector<glMaterial> readMaterials(const char* file);


#endif //SDL2_ENGINE_OBJ_HPP
