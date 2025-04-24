//
// Created by NewDevInC on 20.4.2025.
//

#ifndef SDL2_ENGINE_UTIL_HPP
#define SDL2_ENGINE_UTIL_HPP

typedef unsigned char byte;

#include <cstdio>
#include <cstring>
#include <cstdlib>


inline byte* readFileIntoString(const char* file){
    FILE *fileP;
    long size;
    byte* shaderContent;

    /* Read File to get size */
    fileP = fopen(file, "rb");
    if(fileP == nullptr) {
        return nullptr;
    }
    fseek(fileP, 0L, SEEK_END);
    size = ftell(fileP) + 1;
    fclose(fileP);

    /* Read File for Content */
    fileP = fopen(file, "r");
    shaderContent = (byte*)(memset(malloc(size), '\0', size));
    fread(shaderContent, 1, size-1, fileP);
    fclose(fileP);

    return shaderContent;
}

inline byte* readFileIntoString(const char* file, long &size){
    FILE *fileP;
    byte* shaderContent;

    /* Read File to get size */
    fileP = fopen(file, "rb");
    if(fileP == nullptr) {
        return nullptr;
    }
    fseek(fileP, 0L, SEEK_END);
    size = ftell(fileP) + 1;
    fclose(fileP);

    /* Read File for Content */
    fileP = fopen(file, "r");
    shaderContent = (byte*)(memset(malloc(size), '\0', size));
    fread(shaderContent, 1, size-1, fileP);
    fclose(fileP);

    return shaderContent;
}



inline void getPWD(const char* file, char* &pwd){

    int step = 0, overshoot = 0;

    pwd = (char*)malloc(strlen(file));
    memset((void*)pwd, '\0', strlen(file));

    while(*file != '\0'){
        *file == '/' ? overshoot = 0 : overshoot++;
        file++;
        step++;
    }

    file -= step;

    for(int i = 0; i < step - overshoot; i++){
        *pwd = *file;
        file++;
        pwd++;

    }
    pwd -= step - overshoot;

}


#endif //SDL2_ENGINE_UTIL_HPP
