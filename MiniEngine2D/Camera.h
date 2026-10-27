#pragma once
#include <glad/glad.h>

class Camera {
public:
    float x, y;
    float projectionMatrix[16];

    Camera(float x, float y, int screenWidth, int screenHeight);
    void follow(float targetX, float targetY, int screenWidth, int screenHeight);
    float* getViewMatrix();
    float* getProjectionMatrix();

private:
    float viewMatrix[16];
    void updateViewMatrix(int screenWidth, int screenHeight);
    void updateProjectionMatrix(int screenWidth, int screenHeight);
};