//
// Created by NewDevInC on 27.9.2024.
//


#include <rheniumRenderer.hpp>


int main(int argc, char* argv[]) {
    SDL_Event event;
    auto* renderer = new rheniumRenderer(1080, 1080);

    if(rheniumRenderer::error != 0){
        return -1;
    }

    auto* shader = new glShader("./objects/shaders/default.vert", "./objects/shaders/default.frag");
    auto* mesh = importObj("./objects/suzanne.obj");

    mesh->shader = shader;

    mesh->position = glm::vec3 {0.0f, 0.0f, 0.0f};

    std::vector<vertex> lightVertices = {
            vertex{glm::vec3(-1.0f, -1.0f,  1.0f)},
            vertex{glm::vec3(-1.0f, -1.0f, -1.0f)},
            vertex{glm::vec3(1.0f, -1.0f, -1.0f)},
            vertex{glm::vec3(1.0f, -1.0f,  1.0f)},
            vertex{glm::vec3(-1.0f,  1.0f,  1.0f)},
            vertex{glm::vec3(-1.0f,  1.0f, -1.0f)},
            vertex{glm::vec3(1.0f,  1.0f, -1.0f)},
            vertex{glm::vec3(1.0f,  1.0f,  1.0f)}};

    std::vector<GLuint> lightIndices = {
            0, 1, 2,
            0, 2, 3,
            0, 4, 7,
            0, 7, 3,
            3, 7, 6,
            3, 6, 2,
            2, 6, 5,
            2, 5, 1,
            1, 5, 4,
            1, 4, 0,
            4, 5, 6,
            4, 6, 7
    };

    auto* lightShader = new glShader("./objects/shaders/light.vert", "./objects/shaders/light.frag");
    auto* lightSource = new glMesh(lightShader, lightVertices, lightIndices, "lightSource");

    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

    lightSource->position = glm::vec3(0.5f, 1.0f, 0.5f);



    lightSource->worldMatrix = glm::translate(lightSource->worldMatrix, lightSource->position);
    lightSource->worldMatrix = glm::scale(lightSource->worldMatrix, glm::vec3(0.1f));

    lightShader->start();
    glUniformMatrix4fv(glGetUniformLocation(lightShader->id, "worldMatrix"), 1, GL_FALSE, glm::value_ptr(lightSource->worldMatrix));
    glUniform3f(glGetUniformLocation(lightShader->id, "lightColor"), lightColor.x, lightColor.y, lightColor.z);

    mesh->worldMatrix = glm::translate(mesh->worldMatrix, mesh->position);

    shader->start();
    glUniformMatrix4fv(glGetUniformLocation(shader->id, "worldMatrix"), 1, GL_FALSE, glm::value_ptr(mesh->worldMatrix));
    glUniform3f(glGetUniformLocation(shader->id, "lightColor"), lightColor.x, lightColor.y, lightColor.z);
    glUniform3f(glGetUniformLocation(shader->id, "lightPosition"), lightSource->position.x, lightSource->position.y, lightSource->position.z);

    renderer->pushMeshToStack(mesh);
    renderer->pushMeshToStack(lightSource);

    auto* camera = new glCamera((float)1080/1080, glm::vec3(0.0f, 0.0f, 10.0f), 100.0f, 0.1f, 45);

    while (event.type != SDL_QUIT) {

        renderer->render(camera);
        SDL_PollEvent(&event);

    }
    delete lightShader;
    delete shader;
    delete mesh;
    delete lightSource;
    delete camera;
    delete renderer;

    SDL_Quit();

    return 0;
}
