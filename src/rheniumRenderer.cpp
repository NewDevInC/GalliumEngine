//
// Created by NewDevInC on 27.9.2024.
//

#include "rheniumRenderer.hpp"

int rheniumRenderer::error = 0;

rheniumRenderer::rheniumRenderer(GLuint winX, GLuint winY) {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        error = 1;
    }

    if (winX == 0 || winY == 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "Couldn't initialize SDL: Invalid window size. Did you make a typo?");
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);


    this->window = SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, winX, winY,
                                    SDL_WINDOW_OPENGL);
    this->context = SDL_GL_CreateContext(window);

    if (window == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
        error = 2;
    }

    if (glewInit() != GLEW_OK) {
        error = 3;
    }
    glViewport(0, 0, winX, winY);
    glEnable(GL_DEPTH_TEST);
}

void rheniumRenderer::render(glCamera *camera) {
    glClearColor(0.1f, 0.1f, 0.1F, 0xFF); // Background in case we have no skybox
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera->updateMatrix();

    for (auto &mesh : queuedMeshes) {
        mesh->drawMesh(camera);
    }

    SDL_GL_SwapWindow(this->window);
}

void rheniumRenderer::pushMeshToStack(glMesh *&mesh) {
    queuedMeshes.push_back(mesh);
}

void rheniumRenderer::popMeshToStack() {
    queuedMeshes.pop_back();
}

SDL_Window *rheniumRenderer::getWindow() {
    return this->window;
}

rheniumRenderer::~rheniumRenderer() {
    SDL_GL_DeleteContext(this->context);
    SDL_DestroyWindow(this->window);
}
