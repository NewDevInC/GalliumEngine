//
// Created by NewDevInC on 2.10.2024.
//



#include "glShader.hpp"



glShader::glShader(const char *vertexGLSL, const char *fragmentGLSL) {


    char* vC = (char *)readFileIntoString(vertexGLSL);
    char* fC = (char *)readFileIntoString(fragmentGLSL);


    GLuint v_s = glCreateShader(GL_VERTEX_SHADER);
    GLuint f_s = glCreateShader(GL_FRAGMENT_SHADER);


    glShaderSource(v_s, 1, &vC, nullptr);


    glCompileShader(v_s);

    GLint hasComplied;
    char infoLog[1024];
    glGetShaderiv(v_s, GL_COMPILE_STATUS, &hasComplied);
    if (hasComplied == GL_FALSE) {
        glGetShaderInfoLog(v_s, 1024, nullptr, infoLog);
        printf("SHADER_COMPILATION_ERROR for: VERTEX \n %s", infoLog);
    }



    glShaderSource(f_s, 1, &fC, nullptr);


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

    free(vC);
    free(fC);
}

void glShader::start() {
    glUseProgram(this->id);
}

glShader::~glShader() {
    glDeleteProgram(this->id);
}
