#pragma once
#include <glad/glad.h>
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"

class Sprite {
public:
    float x, y;
    float width, height;
    float rotation;
    float r, g, b;

    bool animated;
    int currentFrame;
    int totalFrames;
    float frameTime;
    float animationTimer;

    Sprite(Texture* tex, float x, float y, float w, float h);

    void draw(Shader& shader, Camera& camera, int screenWidth, int screenHeight);
    void setColor(float r, float g, float b);
    bool collidesWith(const Sprite& other) const;

    void setAnimation(int frames, float frameDuration);
    void updateAnimation(float dt);

    ~Sprite();

private:
    Texture* texture;
    unsigned int VAO, VBO, EBO;
};