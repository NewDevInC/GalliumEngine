//
// Created by NewDevInC on 2.10.2024.
//

#ifndef SDL2_ENGINE_CAMERA_HPP
#define SDL2_ENGINE_CAMERA_HPP
#define GLM_ENABLE_EXPERIMENTAL

#include<GL/glew.h>
#include<SDL.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include <GL/VBO.hpp>
#include <GL/VAO.hpp>
#include <GL/EBO.hpp>
#include <GL/glShader.hpp>

class glCamera {
public:
    // Stores the main vectors of the camera
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    float aspectRatio = 1.0f;

    glCamera(float aspectRatio, glm::vec3 position);

    void updateMatrix(float fov, float nearPlane, float farPlane);

    void exportMatrix(glShader *shader, const char *uniform);

private:
    glm::mat4 matrix = glm::mat4(1.0f);

};


#endif //SDL2_ENGINE_CAMERA_HPP
