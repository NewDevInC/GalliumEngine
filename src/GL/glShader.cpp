//
// Created by NewDevInC on 2.10.2024.
//



#include "glShader.hpp"


char* glShader::loadShader(const char *file) {
    FILE *fp;
    long size = 0;
    char* shaderContent;

    /* Read File to get size */
    fp = fopen(file, "rb");
    if(fp == nullptr) {
        return nullptr;
    }
    fseek(fp, 0L, SEEK_END);
    size = ftell(fp)+1;
    fclose(fp);

    /* Read File for Content */
    fp = fopen(file, "r");
    shaderContent = (char *)(memset(malloc(size), '\0', size));
    fread(shaderContent, 1, size-1, fp);
    fclose(fp);

    return shaderContent;

    }


glShader::glShader(const char *vertexGLSL, const char *fragmentGLSL) {

    // 1. Read the GLSL files
    // 2. preform C++ voodoo magic because apparently this program hates reading things C style

    char* vC = loadShader(vertexGLSL);
    char* fC = loadShader(fragmentGLSL);


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
        printf("SHADER_COMPILATION_ERROR for: VERTEX \n %s", infoLog);
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
        printf("SHADER_COMPILATION_ERROR for: FRAGMENT \n %s", infoLog);
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
