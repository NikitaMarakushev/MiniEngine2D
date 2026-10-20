#pragma once
#pragma once
#include <glad/glad.h>

class Camera {
public:
    float x, y;

    Camera(float x, float y);
    void follow(float targetX, float targetY, int screenWidth, int screenHeight);
    float* getViewMatrix();

private:
    float viewMatrix[16];
    void updateViewMatrix(int screenWidth, int screenHeight);
};