#include "Texture.h"
#include "stb_image.h"
#include <iostream>

Texture::Texture(const char* path) {
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, nullptr, 4);

    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        std::cout << "Loaded texture: " << path << " (" << width << "x" << height << ")" << std::endl;
        stbi_image_free(data);
    }
    else {
        std::cout << "WARNING: Failed to load " << path << "! Using checkerboard placeholder." << std::endl;
        width = 64;
        height = 64;
        const int S = 64;
        unsigned char* checker = new unsigned char[S * S * 4];
        for (int y = 0; y < S; y++) {
            for (int x = 0; x < S; x++) {
                bool even = ((x / 8) + (y / 8)) % 2 == 0;
                int i = (y * S + x) * 4;
                checker[i + 0] = even ? 255 : 0;
                checker[i + 1] = even ? 0 : 255;
                checker[i + 2] = 128;
                checker[i + 3] = 255;
            }
        }
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, S, S, 0, GL_RGBA, GL_UNSIGNED_BYTE, checker);
        delete[] checker;
    }
}

void Texture::bind(unsigned int slot) {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, ID);
}

Texture::~Texture() {
    glDeleteTextures(1, &ID);
}