//
// Created by NewDevInC on 27.9.2024.
//


#include <rheniumRenderer.hpp>


/* TODO: When finished with finalizing 3D rendering,
 change the demo app from an old 3D showcase to a mesh loading showcase
 */

int main(int argc, char* argv[]) {
    SDL_Event event;
    auto* renderer = new rheniumRenderer(800, 800);

    if(rheniumRenderer::error != 0){
        return -1;
    }

    auto* shader = new glShader("./objects/shaders/default.vert", "./objects/shaders/defaultMesh.frag");
    auto* cube = importObj("./objects/cube.obj");


    glEnable(GL_DEPTH_TEST);

    auto* camera = new glCamera((float)800/800, glm::vec3(0.0f, 0.0f, 10.0f), 100.0f, 0.1f, 45);

    while (event.type != SDL_QUIT) {

        renderer->render(shader, camera, cube);
        SDL_PollEvent(&event);

    }
    delete shader;

    delete renderer;

    SDL_Quit();

    return 0;
}
