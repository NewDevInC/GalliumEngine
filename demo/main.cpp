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

    auto* shader = new glShader("./objects/shaders/default.vert", "./objects/shaders/default.frag");
    auto* pVAO = new VAO();
    pVAO->bind();

    auto* pVBO = new VBO();
    auto* pEBO = new EBO();

    pVAO->linkAttrib(*pVBO, 0, 3, GL_FLOAT, 8 * sizeof(float), nullptr);
    pVAO->linkAttrib(*pVBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    pVAO->linkAttrib(*pVBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    // Unbind all to prevent accidentally modifying them
    pVAO->unbind();
    pVBO->unbind();
    pEBO->unbind();

    glEnable(GL_DEPTH_TEST);

    auto* camera = new glCamera((float)800/800, glm::vec3(0.0f, 0.0f, 2.0f));

    while (event.type != SDL_QUIT) {

        renderer->render(shader, camera, pVAO, sizeof(indices));
        SDL_PollEvent(&event);

    }
    delete pVAO;
    delete pVBO;
    delete pEBO;
    delete shader;

    delete renderer;

    SDL_Quit();

    return 0;
}
