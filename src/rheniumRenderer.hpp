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
#include <SDL.h>


class rheniumRenderer {
public:
    rheniumRenderer(GLuint winX, GLuint winY);

    ~rheniumRenderer();

    void render(glShader *shader, glCamera *camera, glMesh* mesh);

    static int error;

    SDL_Window *getWindow();

#ifdef BARE_METAL
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
#else

private:
    SDL_Window *window = nullptr;
    SDL_GLContext context = nullptr;


#endif
};


#endif //SDL2_ENGINE_RHENIUMRENDERER_HPP
