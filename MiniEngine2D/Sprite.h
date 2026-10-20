#pragma once
#include <glad/glad.h>
#include "Shader.h"
#include "Texture.h"

class Sprite {
public:
    float x, y;
    float width, height;
    float rotation;

    Sprite(Texture* tex, float x, float y, float w, float h);
    void draw(Shader& shader, int screenWidth, int screenHeight);
    ~Sprite();

private:
    Texture* texture;
    unsigned int VAO, VBO, EBO;
};