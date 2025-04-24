//
// Created by NewDevInC on 19.4.2025.
//

#include "texture.hpp"

texture::texture(const char *imageSrc, const char *type, GLuint slot) {
    this->type = type;
    int width, height;
    int colourChannelType;
    png_bytep imgData = nullptr;

    readPng(imageSrc, width, height, colourChannelType, imgData);

    if(imgData != nullptr) {

        glGenTextures(1, &this->id);

        glActiveTexture(GL_TEXTURE0 + slot);
        this->unit = slot;
        glBindTexture(GL_TEXTURE_2D, this->id);

        // Configures the type of algorithm that is used to make the image smaller or bigger
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        // Configures the way the texture repeats (if it does at all)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, colourChannelType, GL_UNSIGNED_BYTE, (GLvoid*) imgData);

        glGenerateMipmap(GL_TEXTURE_2D);

        free(imgData);

    }

    unbind();


}

void texture::assignUnit(glShader *&shader, const char *uniform, GLuint unit) {
    shader->start();

    glUniform1i(glGetUniformLocation(shader->id, uniform), unit);
}

void texture::bind() {
    glActiveTexture(GL_TEXTURE0 + this->unit);
    glBindTexture(GL_TEXTURE_2D, this->id);
}

void texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

texture::~texture() {
    glDeleteTextures(1, &this->id);
}

void readPng(const char* imageSrc, int &width, int &height, int &colourChannelType, png_bytep &imgData){

    FILE* file = fopen(imageSrc, "rb");

    png_byte header[8];

    fread(header, 1, 8, file);

    if(!png_sig_cmp(header, 0, 8)) {

        printf("File is not a png. Did you pass the correct file?");

        fclose(file);
    }


    png_structp readPng = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);

    if(!readPng) fclose(file);

    png_infop info = png_create_info_struct(readPng);

    if(!info) fclose(file);

    if(setjmp(png_jmpbuf(readPng))) fclose(file);

    png_init_io(readPng, file);

    png_read_info(readPng, info);

    width = png_get_image_width(readPng, info);
    height = png_get_image_height(readPng, info);
    switch (png_get_color_type(readPng, info)){
        case PNG_COLOR_TYPE_RGBA:
            colourChannelType = GL_RGBA;
            break;
        case PNG_COLOR_TYPE_RGB:
            colourChannelType = GL_RGB;
            break;
    }

    size_t rowBytes = png_get_rowbytes(readPng, info);

    imgData = (png_bytep) malloc(rowBytes * height * sizeof(png_byte));

    png_destroy_read_struct(&readPng, &info, nullptr);

    fclose(file);


}


