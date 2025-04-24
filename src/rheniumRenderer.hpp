//
// Created by NewDevInC on 27.9.2024.
//

#ifndef SDL2_ENGINE_RHENIUMRENDERER_HPP
#define SDL2_ENGINE_RHENIUMRENDERER_HPP

#include <GL/VBO.hpp>
#include <GL/VAO.hpp>
#include <GL/EBO.hpp>
#include <GL/glShader.hpp>
#include <GL/camera.hpp>

#include <import/OBJ.hpp>

#include <genericEntity.hpp>
#include <gameEntity.hpp>
#include <lightEntity.hpp>

#include <memory>
#include <SDL.h>


class rheniumRenderer {
public:
    rheniumRenderer(GLuint winX, GLuint winY);

    ~rheniumRenderer();

    void render(glCamera *camera);

    void bindShaderToEntity(GLuint id, std::shared_ptr<glShader> &shader);

    void addEntityToRenderStack(std::shared_ptr<genericEntity> entity);
    void popEntityFromRenderStack();

    static int error;

    SDL_Window *getWindow();

#ifdef BARE_METAL
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    std::vector<glMesh*> queuedMeshes = {};
#else

private:
    SDL_Window *window = nullptr;
    SDL_GLContext context = nullptr;
    std::vector<std::shared_ptr<genericEntity>> rendererEntity = {};
    std::map<GLuint, std::shared_ptr<glShader>> shaders = {};


#endif
};


#endif //SDL2_ENGINE_RHENIUMRENDERER_HPP
