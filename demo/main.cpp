//
// Created by NewDevInC on 27.9.2024.
//


#include <rheniumRenderer.hpp>


int main(int argc, char* argv[]) {
    SDL_Event event;
    auto* renderer = new rheniumRenderer(1080, 1080);

    if(rheniumRenderer::error != 0){
        return rheniumRenderer::error;
    }

    std::shared_ptr<glShader> shader(new glShader("./objects/shaders/default.vert", "./objects/shaders/default.frag"));
    std::unique_ptr<gameEntity> pGameEntity = importObj("./objects/MultiMat.obj");

    pGameEntity->shaderId = shader->id;

    renderer->bindShaderToEntity(pGameEntity->shaderId, shader);

    pGameEntity->position = glm::vec3 {0.0f, 0.0f, 0.0f};

    std::unique_ptr<lightEntity> lightSource(new lightEntity());

    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

    lightSource->position = glm::vec3(0.0f, 1.0f, 0.0f);
    lightSource->colour = lightColor * 0.5f;

    renderer->addEntityToRenderStack(reinterpret_cast<std::shared_ptr<genericEntity> &&>(pGameEntity));
    renderer->addEntityToRenderStack(reinterpret_cast<std::shared_ptr<genericEntity> &&>(lightSource));

    auto* camera = new glCamera((float)1080/1080, glm::vec3(0.0f, 0.0f, 10.0f), 100.0f, 0.1f, 45);

    camera->position = glm::vec3(0.0f, 1.0f, 10.0f);

    while (event.type != SDL_QUIT) {

        renderer->render(camera);
        SDL_PollEvent(&event);

    }

    delete camera;
    delete renderer;

    SDL_Quit();

    return 0;
}
