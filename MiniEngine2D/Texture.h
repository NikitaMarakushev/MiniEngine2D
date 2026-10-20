#pragma once
#include <glad/glad.h>
#include <string>

class Texture {
public:
    unsigned int ID;
    int width, height;

    Texture(const char* path);
    void bind(unsigned int slot = 0);
    ~Texture();
};