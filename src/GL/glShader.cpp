//
// Created by NewDevInC on 2.10.2024.
//


#include "glShader.hpp"


void glShader::loadShader(const char *file, char *&output) {

    FILE *source = fopen(file, "r");
    fseek(source, 0, SEEK_END);
    int size = ftell(source);
    rewind(source);
    output = (char *) malloc(size);
    char c;

    while ((c = fgetc(source)) != EOF) {
        *output = c;
        output++;
    }

    output++;
    *output = '\0';
    output--;

    rewind(source);
    while (fgetc(source) != EOF) {
        output--;
    }

    fclose(source);

}

glShader::glShader(const char *vertexGLSL, const char *fragmentGLSL) {

    // 1. Read the GLSL files
    // 2. gib GLSL to OpenGL

    char *vC = nullptr;
    loadShader(vertexGLSL, vC);

    char *fC = nullptr;
    loadShader(fragmentGLSL, fC);


    GLuint v_s = glCreateShader(GL_VERTEX_SHADER);
    GLuint f_s = glCreateShader(GL_FRAGMENT_SHADER);

    if (vertexGLSL == nullptr || vC == nullptr) {
        glShaderSource(v_s, 1, &this->defaultVertexShader, nullptr);
    } else {
        glShaderSource(v_s, 1, &vC, nullptr);
    }

    glCompileShader(v_s);

    GLint hasComplied;
    char infoLog[1024];
    glGetShaderiv(v_s, GL_COMPILE_STATUS, &hasComplied);
    if (hasComplied == GL_FALSE) {
        glGetShaderInfoLog(v_s, 1024, nullptr, infoLog);
        std::cout << "SHADER_COMPILATION_ERROR for:" << "VERTEX" << "\n" << infoLog << std::endl;
    }


    if (fragmentGLSL == nullptr || fC == nullptr) {
        glShaderSource(f_s, 1, &this->defaultFragmentShader, nullptr);
    } else {
        glShaderSource(f_s, 1, &fC, nullptr);
    }

    glCompileShader(f_s);

    hasComplied = 0;
    glGetShaderiv(f_s, GL_COMPILE_STATUS, &hasComplied);
    if (hasComplied == GL_FALSE) {
        glGetShaderInfoLog(f_s, 1024, nullptr, infoLog);
        std::cout << "SHADER_COMPILATION_ERROR for:" << "FRAGMENT" << "\n" << infoLog << std::endl;
    }

    this->id = glCreateProgram();
    glAttachShader(this->id, v_s);
    glAttachShader(this->id, f_s);

    glLinkProgram(this->id);

    glDeleteShader(v_s);
    glDeleteShader(f_s);

    // We don't need to hog system memory with files we use only once

    /*free(vC);
    free(fC);*/
}

void glShader::start() {
    glUseProgram(this->id);
}

glShader::~glShader() {
    glDeleteProgram(this->id);
}
