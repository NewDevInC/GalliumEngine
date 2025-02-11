//
// Created by NewDevInC on 2.10.2024.
//

#ifndef SDL2_ENGINE_GLSHADER_HPP
#define SDL2_ENGINE_GLSHADER_HPP

#include <GL/glew.h>
#include <cstdio>
#include <cstdlib>

class glShader {

public:
    GLuint id;

    void loadShader(const char *file, char *&output);

    glShader(const char *vertexGLSL, const char *fragmentGLSL);

    ~glShader();

    void start();

private:

    // TODO: Should probably do error checking, until then... say hello to default frags!

    const char *defaultVertexShader = "#version 330 core\n"
                                      "\n"
                                      "// Positions/Coordinates\n"
                                      "layout (location = 0) in vec3 aPos;\n"
                                      "// Colors\n"
                                      "layout (location = 1) in vec3 aColor;\n"
                                      "// Texture Coordinates\n"
                                      "layout (location = 2) in vec2 aTex;\n"
                                      "\n"
                                      "\n"
                                      "// Outputs the color for the Fragment Shader\n"
                                      "out vec3 color;\n"
                                      "// Outputs the texture coordinates to the fragment shader\n"
                                      "out vec2 texCoord;\n"
                                      "\n"
                                      "// Imports the camera matrix from the main function\n"
                                      "uniform mat4 cameraMatrix;\n"
                                      "\n"
                                      "\n"
                                      "void main()\n"
                                      "{\n"
                                      "    // Outputs the positions/coordinates of all vertices\n"
                                      "    gl_Position = cameraMatrix * vec4(aPos, 1.0);\n"
                                      "    // Assigns the colors from the Vertex Data to \"color\"\n"
                                      "    color = aColor;\n"
                                      "    // Assigns the texture coordinates from the Vertex Data to \"texCoord\"\n"
                                      "    texCoord = aTex;\n"
                                      "}";

    const char *defaultFragmentShader = "#version 330 core\n"
                                        "\n"
                                        "// Outputs colors in RGBA\n"
                                        "out vec4 FragColor;\n"
                                        "\n"
                                        "\n"
                                        "// Inputs the color from the Vertex Shader\n"
                                        "in vec3 color;\n"
                                        "// Inputs the texture coordinates from the Vertex Shader\n"
                                        "in vec2 texCoord;\n"
                                        "\n"
                                        "// Gets the Texture Unit from the main function\n"
                                        "uniform sampler2D tex0;\n"
                                        "\n"
                                        "\n"
                                        "void main()\n"
                                        "{\n"
                                        "    FragColor = vec4(color, 1.0f);\n"
                                        "\n"
                                        "}";
};


#endif //SDL2_ENGINE_GLSHADER_HPP
